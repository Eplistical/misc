#ifndef _MPIER_HPP
#define _MPIER_HPP
/* module for MPI
 *
 * Gaohan
 */
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstdint>
#include <limits>
#include <random>
#include "types.hpp"
#include "type_traiter.hpp"
#include "mpi.h"

namespace MPIer {
	using namespace std;
	using namespace type_traiter;

	// -- vars -- //
	// normal type -> MPI TYPE mapping
	using MPI_PREDIFINED_DATA_T = decltype(MPI_INT);
	static std::unordered_map<type_index, MPI_PREDIFINED_DATA_T> typemap
		= { 
			{typeid(CHAR_T), MPI_CHAR},
			{typeid(INT_T), MPI_INT32_T},
			{typeid(UINT_T), MPI_UINT32_T},
			{typeid(DOUBLE_T), MPI_DOUBLE},
		};
	// MPI Windows
	std::vector<MPI_Win> win_vec;

	// all-communicator variables
	static INT_T size;
	static INT_T rank;
	static BOOL_T master;

	// shared-memory communicator variable
	static MPI_Comm comm_sm;
	static INT_T size_sm;
	static INT_T rank_sm;
	static BOOL_T master_sm;
	static BOOL_T sm_flag;

	// -- init/finalize --//
	inline VOID_T setup(VOID_T) 
	{
		MPI::Init();
		size = MPI::COMM_WORLD.Get_size();
		rank = MPI::COMM_WORLD.Get_rank();
		master = (rank == 0);

		// shared-memory not opened
		sm_flag = false;
	}

	inline VOID_T finalize(VOID_T) 
	{
		MPI::Finalize();
	}

	inline VOID_T abort(INT_T errorcode = MPI_ERR_OTHER) 
	{
		MPI::COMM_WORLD.Abort(errorcode);
	}

	// -- barrier -- //
	inline VOID_T barrier(VOID_T) 
	{
		MPI::COMM_WORLD.Barrier();
	}

	// -- send -- //
	inline VOID_T send(INT_T to){  }

	template<typename ParamType>
		inline typename enable_if<is_fundamental<ParamType>::value && (!is_bool<ParamType>::value), VOID_T>::type
		send(INT_T to, ParamType& x)
		{
			INT_T tag = rank; // default tag: rank of from thread
			MPI::COMM_WORLD.Send(&x, 1, typemap[typeid(ParamType)], to, tag);
		}

	template<typename ParamType>
		inline typename enable_if<is_bool<ParamType>::value, VOID_T>::type
		send(INT_T to, ParamType& x) 
		{
			INT_T tag = rank; // default tag: rank of from thread
			INT_T tmp = static_cast<INT_T>(x);
			MPI::COMM_WORLD.Send(&tmp, 1, typemap[typeid(INT_T)], to, tag);
		}

	template<typename ParamType>
		inline typename enable_if<is_vector<ParamType>::value || is_string<ParamType>::value, VOID_T>::type
		send(INT_T to, ParamType& x)
		{
			INT_T tag = rank; // default tag: rank of from thread
			UINT_T _size = x.size();
			MPI::COMM_WORLD.Send(&_size, 1, typemap[typeid(UINT_T)], to, tag);
			if (_size != 0) {
				MPI::COMM_WORLD.Send(&x[0], x.size(), typemap[typeid(typename ParamType::value_type)], to, tag);
			}
		}

	template<typename ParamType, typename ... Types>
		inline VOID_T send(INT_T to, ParamType& x, Types& ... otherx)
		{
			send(to, x);
			send(to, otherx ...);
		}

	// -- recv -- //
	inline VOID_T recv(INT_T from){  }

	template<typename ParamType>
		inline typename enable_if<is_fundamental<ParamType>::value && (!is_bool<ParamType>::value), VOID_T>::type
		recv(INT_T from, ParamType& x)
		{
			INT_T tag = from; // default tag: rank of from thread
			MPI::COMM_WORLD.Recv(&x, 1, typemap[typeid(ParamType)], from, tag);
		}

	template<typename ParamType>
		inline typename enable_if<is_bool<ParamType>::value, VOID_T>::type
		recv(INT_T from, ParamType& x) 
		{
			INT_T tag = from; // default tag: rank of from thread
			INT_T tmp;
			MPI::COMM_WORLD.Recv(&tmp, 1, typemap[typeid(INT_T)], from, tag);
			x = static_cast<BOOL_T>(tmp);
		}

	template<typename ParamType>
		inline typename enable_if<is_vector<ParamType>::value || is_string<ParamType>::value, VOID_T>::type
		recv(INT_T from, ParamType& x)
		{
			INT_T tag = from; // default tag: rank of from thread
			UINT_T _size;
			MPI::COMM_WORLD.Recv(&_size, 1, typemap[typeid(UINT_T)], from, tag);
			x.resize(_size);
			if (_size != 0) {
				MPI::COMM_WORLD.Recv(&x[0], x.size(), typemap[typeid(typename ParamType::value_type)], from, tag);
			}
		}

	template<typename ParamType, typename ... Types>
		inline VOID_T recv(INT_T from, ParamType& x, Types& ... otherx)
		{
			recv(from, x);
			recv(from, otherx ...);
		}
	
	
	// -- bcast -- //
	inline VOID_T bcast(INT_T root){  }

	template<typename ParamType>
		inline typename enable_if<is_fundamental<ParamType>::value && (!is_bool<ParamType>::value), VOID_T>::type
		bcast(INT_T root, ParamType& x)
		{
			MPI::COMM_WORLD.Bcast(&x, 1, typemap[typeid(ParamType)], root);
		}

	template<typename ParamType>
		inline typename enable_if<is_bool<ParamType>::value, VOID_T>::type
		bcast(INT_T root, ParamType& x) 
		{
			INT_T tmp = static_cast<INT_T>(x);
			MPI::COMM_WORLD.Bcast(&tmp, 1, typemap[typeid(INT_T)], root);
			x = static_cast<BOOL_T>(tmp);
		}

	template<typename ParamType>
		inline typename enable_if<is_vector<ParamType>::value || is_string<ParamType>::value, VOID_T>::type
		bcast(INT_T root, ParamType& x)
		{
			UINT_T _size = x.size();
			MPI::COMM_WORLD.Bcast(&_size, 1, typemap[typeid(UINT_T)], root);
			if (not master) x.resize(_size);
			MPI::COMM_WORLD.Bcast(&x[0], x.size(), typemap[typeid(typename ParamType::value_type)], root);
		}

	template<typename ParamType, typename ... Types>
		inline VOID_T bcast(INT_T root, ParamType& x, Types& ... otherx)
		{
			bcast(root, x);
			bcast(root, otherx ...);
		}


	// -- utilities -- //
	inline std::vector<UINT_T> assign_job_start_and_num(UINT_T Njob)
	{
		/**
		 * given a total Njobs
		 * return a vector {StartJobIndex, JobNumber} for current process
		 */
		UINT_T quotient = Njob / size;
		UINT_T remainder = Njob % size;
		std::vector<UINT_T> rst(2);
		if (rank < remainder) {
			rst[0] = (quotient + 1) * rank;
			rst[1] = quotient + 1;
		}
		else {
			rst[0] = quotient * rank + remainder;
			rst[1] = quotient;
		}
		return rst;
	}

	template<typename T>
	inline std::vector<T> assign_job(std::vector<T> Jobs)
	{
		/**
		 * given a vector of all jobs,
		 * return a vector of jobs for current process
		 */
		std::vector<UINT_T> mybatch = assign_job_start_and_num(Jobs.size());
		return std::vector<T>(Jobs.begin() + mybatch[0], Jobs.begin() + mybatch[0] + mybatch[1]);
	}

	inline std::vector<UINT_T> assign_job(UINT_T Njob)
	{
		/**
		 * given total # of jobs
		 * return a vector continuous job indices
		 */
		vector<UINT_T> Jobs(Njob);
		if (master) {
			for (UINT_T i = 0; i < Jobs.size(); ++i) 
				Jobs[i] = i;
		}
		bcast(0, Jobs);
		std::vector<UINT_T> mybatch = assign_job(Jobs);
		return mybatch;
	}

	inline std::vector<UINT_T> assign_job_random(UINT_T Njob)
	{
		/**
		 * given total # of jobs
		 * return a vector of random job indices
		 */
		vector<UINT_T> Jobs(Njob);
		if (master) {
			for (UINT_T i = 0; i < Jobs.size(); ++i) 
				Jobs[i] = i;
			std::random_shuffle(Jobs.begin(), Jobs.end()); 
		}
		bcast(0, Jobs);
		std::vector<UINT_T> mybatch = assign_job(Jobs);
		return mybatch;
	}

	inline UINT_T assign_random_seed(UINT_T raw_seed = 0) noexcept
	{
		std::mt19937 rng(raw_seed);
		std::uniform_int_distribution<UINT_T> dist(0, std::numeric_limits<UINT_T>::max());
		UINT_T rst(raw_seed);
		for (UINT_T i(0); i < rank; ++i) {
			rst = dist(rng);
		}
		return rst;
	}


	// -- setup_sm -- //
	VOID_T setup_sm(VOID_T) {
		if (!sm_flag) {
			MPI_Comm_split_type(MPI::COMM_WORLD, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, &comm_sm);
			MPI_Comm_rank(comm_sm, &rank_sm);
			MPI_Comm_size(comm_sm, &size_sm);
			master_sm = (rank_sm == 0);
			sm_flag = true;
		}
	}

	// -- make_sm -- //
	template<typename ParamType>
		inline typename enable_if<is_fundamental<ParamType>::value && (!is_bool<ParamType>::value), VOID_T>::type
	make_sm(INT_T root, ParamType*& data_ptr, UINT_T N) 
	{
		if (N == 0) return;

		INT_T disp_unit = sizeof(ParamType);
		MPI_Aint WINSIZE = static_cast<MPI_Aint>(N) * static_cast<MPI_Aint>(disp_unit); // cast to avoid overflow
		win_vec.push_back(MPI_Win());
		MPI_Win& win_sm = win_vec.back();
		ParamType* orig = data_ptr;

		// create shared memory
		if (rank_sm == root) {
			// alloc share mem on master
			MPI_Win_allocate_shared(WINSIZE, disp_unit, MPI_INFO_NULL, comm_sm, &data_ptr, &win_sm);
			// copy data to shared memory
			memcpy(data_ptr, orig, WINSIZE);
		}
		else {
			// query shared mem on non-master
			MPI_Win_allocate_shared(0, disp_unit, MPI_INFO_NULL, comm_sm, &data_ptr, &win_sm);
			MPI_Win_shared_query(win_sm, root, &WINSIZE, &disp_unit, &data_ptr);
		}

		// synchoronize
		MPI_Win_fence(0, win_sm);
	}
};


#endif
