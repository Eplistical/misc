#ifndef _IOER_STREAM_IO_MGR_HPP
#define _IOER_STREAM_IO_MGR_HPP
// module for ioer::stream_io_mgr
// stream I/O manager class
// THIS IS A SINGLETON

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "ioer_macros.hpp"
#include "ioer_exceptions.hpp"
#include "io_pathtracker.hpp"

namespace ioer 
{
	using namespace std;
	const string STDIO_PATH("");

	class stream_io_mgr 
	{
		private:
			stream_io_mgr() = default;

		public:
			~stream_io_mgr() = default;
			static stream_io_mgr& getInstance() 
			{
				static stream_io_mgr stream_io_mgr_singleton;
				return stream_io_mgr_singleton;
			}

			// no copy
			stream_io_mgr(const stream_io_mgr& other) = delete;
			stream_io_mgr& operator=(const stream_io_mgr& other) = delete;

		public:
			void open(const string& path, ios::openmode mode)
			{
				if (!path.empty()) {
					if (path_exist(path))
						return;
					_fpdict[path] = fstream(path, mode);
					if (not _fpdict.at(path).is_open()){
						ostringstream errmsg;
						errmsg << "ioer::stream_io_mgr::open : Unable to open file "
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
					errmsg << "ioer::stream_io_mgr::at : "
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

	}; // class stream_io_mgr

}; // namespace ioer

#endif // _IOER_STREAM_IO_MGR_HPP
