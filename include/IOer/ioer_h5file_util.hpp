#ifndef _IOER_H5FILE_UTIL_HPP
#define _IOER_H5FILE_UTIL_HPP
/* module for hdf5 file utilities in ioer
 *
 * Gaohan
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <utility>
#include "../type_traiter.hpp"
#include "ioer_macros.hpp"
#include "ioer_exceptions.hpp"
#include "hdf5_io_mgr.hpp"

namespace ioer
{
	using namespace std;
	using namespace type_traiter;

	static const std::map<type_index, H5::DataType> h5_dtype_dict
		= {
			{typeid(char), H5::PredType::NATIVE_CHAR},
			{typeid(int), H5::PredType::NATIVE_INT},
			{typeid(unsigned int), H5::PredType::NATIVE_UINT},
			{typeid(long), H5::PredType::NATIVE_LONG},
			{typeid(long long), H5::PredType::NATIVE_LLONG},
			{typeid(uint32_t), H5::PredType::NATIVE_INT32},
			{typeid(uint64_t), H5::PredType::NATIVE_INT64},
			{typeid(double), H5::PredType::NATIVE_DOUBLE},
			{typeid(long double), H5::PredType::NATIVE_LDOUBLE}
		};

	class h5file_t 
	{
		public:
			using path_type = hdf5_io_mgr::path_type;
			using file_type = hdf5_io_mgr::file_type;
			using key_type = std::string;

		public:
			h5file_t(const string& path, ios::openmode mode)
			{ 
				open(path, mode);
			}

			// no copy 
			h5file_t(const h5file_t&) = delete;
			h5file_t& operator=(const h5file_t&) = delete;

		public:
			// open/close
			void open(const path_type& path, ios::openmode mode) 
			{
				_path = path;
				_mode = mode;
				_hdf5_io_mgr_sing.open(path, mode);
			}

			void close(void) 
			{
				_hdf5_io_mgr_sing.close(_path);
			}

		public:
			template <typename DType>
				void create_dataset(const key_type& ds_key, const std::vector<DType>& buf) {
					if (not buf.empty()) {
						hsize_t dim(buf.size());
						H5::DataType dtype(getH5PredType(buf.at(0)));
						H5::DataSpace dspace(1, &dim);
						H5::DataSet ds(_hdf5_io_mgr_sing.at(_path).createDataSet(ds_key, dtype, dspace));
						ds.write(buf.data(), dtype);
					}
				}

			template <typename AType>
				void create_attr(const key_type& ds_key, const key_type& attr_key, const AType& val) {
					H5::DataType dtype(getH5PredType(val));
					H5::DataSpace dspace(H5S_SCALAR);
					_hdf5_io_mgr_sing.at(_path).openDataSet(ds_key).createAttribute(attr_key, dtype, dspace).write(dtype, &val);
				}

		public:
			template <typename DType>
				void read_dataset(const key_type& ds_key, std::vector<DType>& buf) {
					static std::vector<hsize_t> dims;
					H5::DataSet ds = _hdf5_io_mgr_sing.at(_path).openDataSet(ds_key);
					H5::DataSpace dataspace = ds.getSpace();
					dims.resize(dataspace.getSimpleExtentNdims());
					dataspace.getSimpleExtentDims(&dims[0]);
					// read data, only support 1D
					assert(dims.size() == 1);
					buf.resize(dims[0]);
					ds.read(buf.data(), getH5PredType(buf[0]));
				}

			template <typename AType>
				void read_attr(const key_type& ds_key, const key_type& attr_key, AType& val) {
					H5::DataType dtype(getH5PredType(val));
					_hdf5_io_mgr_sing.at(_path).openDataSet(ds_key).openAttribute(attr_key).read(dtype, &val);
				}

		private:
			template <typename DType>
				const H5::DataType& getH5PredType(const DType& val) {
					return h5_dtype_dict.at(typeid(val));
				}

		private:
			hdf5_io_mgr& _hdf5_io_mgr_sing = hdf5_io_mgr::getInstance();
			path_type _path;
			ios::openmode _mode;


	}; // class h5file_t
};
#endif
