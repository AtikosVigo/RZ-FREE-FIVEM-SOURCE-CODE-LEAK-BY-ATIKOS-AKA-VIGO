/*
 * This file is part of the CitizenFX project - http://citizen.re/
 *
 * See LICENSE and MENTIONS in the root of the source tree for information
 * regarding licensing.
 */

#pragma once
#include <cassert>
#include <vector>
#include <string_view>
#include <Windows.h>

#if defined(_CPPUNWIND) && !defined(PATTERNS_SUPPRESS_EXCEPTIONS)
#define PATTERNS_ENABLE_EXCEPTIONS
#endif

namespace hook
{
	template<typename T = char*>
	T get_tls()
	{
		static auto tlsIndex = ([]()
			{
				auto base = (char*)GetModuleHandleA(NULL);
				auto moduleBase = (PIMAGE_DOS_HEADER)base;
				auto ntBase = (PIMAGE_NT_HEADERS)(base + moduleBase->e_lfanew);
				auto tlsBase = (PIMAGE_TLS_DIRECTORY)(base + ntBase->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_TLS].VirtualAddress);

				return reinterpret_cast<uint32_t*>(tlsBase->AddressOfIndex);
			})();

			auto tlsBase = (LPVOID*)__readgsqword(0x58);
			return (T)tlsBase[*tlsIndex];
	}

	struct assert_err_policy
	{
		static void count([[maybe_unused]] bool countMatches) { assert(countMatches); }
	};

#ifdef PATTERNS_ENABLE_EXCEPTIONS
	class txn_exception
	{
		// Deliberately empty for now
	};

#define TXN_CATCH() catch (const hook::txn_exception&) {}

	struct exception_err_policy
	{
		static void count(bool countMatches) { if (!countMatches) { throw txn_exception{}; } }
	};
#else
	struct exception_err_policy
	{
	};
#endif

	class pattern_match
	{
	private:
		void* m_pointer;

	public:
		inline pattern_match(void* pointer)
			: m_pointer(pointer)
		{
		}

		template<typename T>
		T* get(ptrdiff_t offset = 0) const
		{
			char* ptr = reinterpret_cast<char*>(m_pointer);
			return reinterpret_cast<T*>(ptr + offset);
		}
	};

	namespace details
	{
		ptrdiff_t get_process_base();

		class basic_pattern_impl
		{
		protected:
			std::basic_string<uint8_t> m_bytes;
			std::basic_string<uint8_t> m_mask;

#if PATTERNS_USE_HINTS
			uint64_t m_hash = 0;
#endif

			std::vector<pattern_match> m_matches;

			bool m_matched = false;

			uintptr_t m_rangeStart;
			uintptr_t m_rangeEnd;

		protected:
			void Initialize(std::string_view pattern);

			bool ConsiderHint(uintptr_t offset);

			void EnsureMatches(uint32_t maxCount);

			inline pattern_match _get_internal(size_t index) const
			{
				return m_matches[index];
			}

		private:
			explicit basic_pattern_impl(uintptr_t begin, uintptr_t end = 0)
				: m_rangeStart(begin), m_rangeEnd(end)
			{
			}

		public:
			explicit basic_pattern_impl()
				: m_rangeStart(0), m_rangeEnd(0)
			{
			}

			explicit basic_pattern_impl(std::string_view pattern)
				: basic_pattern_impl(get_process_base())
			{
				Initialize(std::move(pattern));
			}

			inline basic_pattern_impl(void* module, std::string_view pattern)
				: basic_pattern_impl(reinterpret_cast<uintptr_t>(module))
			{
				Initialize(std::move(pattern));
			}

			inline basic_pattern_impl(uintptr_t begin, uintptr_t end, std::string_view pattern)
				: basic_pattern_impl(begin, end)
			{
				Initialize(std::move(pattern));
			}

			// Pretransformed patterns
			inline basic_pattern_impl(std::basic_string_view<uint8_t> bytes, std::basic_string_view<uint8_t> mask)
				: basic_pattern_impl(get_process_base())
			{
				assert(bytes.length() == mask.length());
				m_bytes = std::move(bytes);
				m_mask = std::move(mask);
			}

		protected:
#if PATTERNS_USE_HINTS && PATTERNS_CAN_SERIALIZE_HINTS
			// define a hint
			static void hint(uint64_t hash, uintptr_t address);
#endif
		};
	}

	template<typename err_policy>
	class basic_pattern : details::basic_pattern_impl
	{
	public:
		using details::basic_pattern_impl::basic_pattern_impl;

		inline basic_pattern&& count(uint32_t expected)
		{
			EnsureMatches(expected);
			err_policy::count(m_matches.size() == expected);
			return std::forward<basic_pattern>(*this);
		}

		inline basic_pattern&& count_hint(uint32_t expected)
		{
			EnsureMatches(expected);
			return std::forward<basic_pattern>(*this);
		}

		inline basic_pattern&& clear(void* module = nullptr)
		{
			if (module)
			{
				this->m_rangeStart = reinterpret_cast<uintptr_t>(module);
				this->m_rangeEnd = 0;
			}

			m_matches.clear();
			m_matched = false;
			return std::forward<basic_pattern>(*this);
		}

		inline size_t size()
		{
			EnsureMatches(UINT32_MAX);
			return m_matches.size();
		}

		inline bool empty()
		{
			return size() == 0;
		}

		inline pattern_match get(size_t index)
		{
			EnsureMatches(UINT32_MAX);
			return _get_internal(index);
		}

		inline pattern_match get_one()
		{
			return std::forward<basic_pattern>(*this).count(1)._get_internal(0);
		}

		template<typename T = void>
		inline auto get_first(ptrdiff_t offset = 0)
		{
			return get_one().get<T>(offset);
		}

		template <typename Pred>
		inline Pred for_each_result(Pred&& pred)
		{
			EnsureMatches(UINT32_MAX);
			for (auto it : m_matches)
			{
				std::forward<Pred>(pred)(it);
			}
			return std::forward<Pred>(pred);
		}

	public:
#if PATTERNS_USE_HINTS && PATTERNS_CAN_SERIALIZE_HINTS
		// define a hint
		static void hint(uint64_t hash, uintptr_t address)
		{
			details::basic_pattern_impl::hint(hash, address);
		}
#endif
	};

	using pattern = basic_pattern<assert_err_policy>;

	inline auto make_module_pattern(void* module, std::string_view bytes)
	{
		return pattern(module, std::move(bytes));
	}

	inline auto make_range_pattern(uintptr_t begin, uintptr_t end, std::string_view bytes)
	{
		return pattern(begin, end, std::move(bytes));
	}

	template<typename T = void>
	inline auto get_pattern(std::string_view pattern_string, ptrdiff_t offset = 0)
	{
		return pattern(std::move(pattern_string)).get_first<T>(offset);
	}

	inline auto module_pattern(void* module, std::string_view bytes)
	{
		return make_module_pattern(module, std::move(bytes));
	}

	inline auto range_pattern(uintptr_t begin, uintptr_t end, std::string_view bytes)
	{
		return make_range_pattern(begin, end, std::move(bytes));
	}

	namespace txn
	{
		using pattern = hook::basic_pattern<exception_err_policy>;

		inline auto make_module_pattern(void* module, std::string_view bytes)
		{
			return pattern(module, std::move(bytes));
		}

		inline auto make_range_pattern(uintptr_t begin, uintptr_t end, std::string_view bytes)
		{
			return pattern(begin, end, std::move(bytes));
		}

		template<typename T = void>
		inline auto get_pattern(std::string_view pattern_string, ptrdiff_t offset = 0)
		{
			return pattern(std::move(pattern_string)).get_first<T>(offset);
		}

		inline auto module_pattern(void* module, std::string_view bytes)
		{
			return make_module_pattern(module, std::move(bytes));
		}

		inline auto range_pattern(uintptr_t begin, uintptr_t end, std::string_view bytes)
		{
			return make_range_pattern(begin, end, std::move(bytes));
		}
	}

	template<typename T = void, size_t Len>
	auto get_pattern_sec(const char(&pattern_string)[Len], ptrdiff_t offset = 0)
	{
		return hook::pattern(pattern_string).get_first<T>(offset);
	}

	template<typename T = void>
	auto get_pattern_sec(std::string_view pattern_view, ptrdiff_t offset = 0)
	{
		return  hook::pattern(pattern_view).get_first<T>(offset);
	}

	inline ptrdiff_t baseAddressDifference;

	inline constexpr uintptr_t exe_end()
	{

		return 0x146000000;
	}

	inline void set_base(uintptr_t address)
	{
		uintptr_t addressDiff = (address - 0x140000000);
		baseAddressDifference = *(ptrdiff_t*)&addressDiff;
	}

	// sets the base to the process main base
	inline void set_base()
	{
		set_base((uintptr_t)GetModuleHandleA(NULL));
	}

	template<typename T>
	inline void adjust_base(T& address)
	{
		if ((uintptr_t)address >= 0x140000000 && (uintptr_t)address <= exe_end())
		{
			*(uintptr_t*)&address += baseAddressDifference;
		}
	}

	template<typename T>
	inline uintptr_t get_adjusted(T address)
	{
		if ((uintptr_t)address >= 0x140000000 && (uintptr_t)address <= exe_end())
		{
			return (uintptr_t)address + baseAddressDifference;
		}

		return (uintptr_t)address;
	}

	template<typename T, typename TAddr>
	inline T get_address(TAddr address)
	{
		intptr_t target = *(int32_t*)(get_adjusted(address));
		target += (get_adjusted(address) + 4);

		return (T)target;
	}

	template<typename T, typename TAddr>
	inline T get_address(TAddr address, size_t offsetTo4ByteAddr, size_t numBytesInLine)
	{
		intptr_t target = *(int32_t*)(get_adjusted((char*)address + offsetTo4ByteAddr));
		target += (get_adjusted(address) + numBytesInLine);

		return (T)target;
	}
}