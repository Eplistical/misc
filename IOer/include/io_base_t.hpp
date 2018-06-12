#ifndef _IOER_IO_BASE_T_HPP
#define _IOER_IO_BASE_T_HPP
// module for ioer::io_base_t

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "ioer_macros.hpp"
#include "ioer_exceptions.hpp"

namespace ioer 
{
	using namespace std;
	const string STDIO_PATH("");

	class io_base_t 
	{
		public:
			io_base_t() = default;

			io_base_t(const string& path, ios::openmode mode) noexcept
			{
				open(path, mode);	
			}

			virtual ~io_base_t() = default;

			// no copy
			io_base_t(const io_base_t& other) = delete;
			io_base_t& operator=(const io_base_t& other) = delete;

		public:
			void open(const string& path, ios::openmode mode)
			{
				if (!path.empty()) {
					if (path_exist(path))
						return;
					_fpdict[path] = fstream(path, mode);
					if (not _fpdict.at(path).is_open()){
						ostringstream errmsg;
						errmsg << "ioer::io_base_t::open : Unable to open file "
							<< path << ".";
						throw FileNotOpenedError(errmsg.str());
					}
				}
			}

			void close(const string& path) noexcept
			{
				if (path != STDIO_PATH) {
					auto it = _fpdict.find(path);
					if (it != _fpdict.end()) {
						it->second.close();
						_fpdict.erase(it);
					}
				}
			}

		public:
			size_t size() const noexcept
			{
				return _fpdict.size(); 
			}

			iostream& operator[](const string& path) 
			{
				return static_cast<iostream&>
					( (is_stdio(path) ? cout : _fpdict[path]) );
			}

			iostream& at(const string& path)
			{
				try {
					return static_cast<iostream&>
						( (is_stdio(path) ? cout : _fpdict.at(path)) );
				} catch(const out_of_range& e) {
					ostringstream errmsg;
					errmsg << "ioer::io_base_t::at : "
						<< path << " not opened.";
					throw FileNotOpenedError(errmsg.str());
				}
			}


		protected:
			bool path_exist(const string& path) const noexcept
			{ 
				return (_fpdict.find(path) != _fpdict.end()); 
			}

			bool is_stdio(const string& path) const noexcept
			{ 
				return (path == ioer::STDIO_PATH); 
			}


		protected:
			unordered_map<string, fstream> _fpdict;

	}; // class io_base_t

}; // namespace ioer

#endif // _IOER_IO_BASE_T_HPP
