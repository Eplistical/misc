#ifndef _IOER_OUTPUT_T_AUX_HPP
#define _IOER_OUTPUT_T_AUX_HPP
/* aux module for output utilities in ioer
 *
 * Gaohan
 */
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "type_traiter.hpp"
#include "ioer_macros.hpp"
#include "io_base_t.hpp"
#include "ioer_var.hpp"
#include "ioer_exceptions.hpp"

namespace ioer 
{
    using std::string;
    using std::size_t;
    using std::iostream;
    using type_traiter::is_direct_outputable;
    using type_traiter::is_sequence_container;
    using ioer::io_base_obj;

    class _pair_output_functor_t 
    {
        public:
            _pair_output_functor_t(const string&, const string&, size_t, bool, bool, bool) noexcept;

        public:
            void config(const string&, const string&, size_t, bool, bool, bool) noexcept;

            template<typename KeyType, typename ValType>
                typename enable_if< is_direct_outputable< ValType >::value, 
                         const _pair_output_functor_t&>::type
                operator()(const KeyType& key, const ValType& val) const;

            template<typename KeyType, typename ValType>
                typename enable_if< is_sequence_container<ValType>::value,
                         const _pair_output_functor_t& >::type
                operator()(const KeyType& key, const ValType& val) const;

        protected:
            string _path; 
            string _dlm;
            size_t _width;
            bool _keyfirst;
            bool _nonewline;
            bool _flush;

    }; // class _pair_output_functor_t

    /* 
     * Implimentation
     */

    /*****************************************************************************/

    _pair_output_functor_t::_pair_output_functor_t(const string& path, 
            const string& dlm, size_t width, 
            bool keyfirst, bool nonewline, 
            bool flush) noexcept : 
        _path(path), _dlm(dlm), 
        _width(width), _keyfirst(keyfirst), 
        _nonewline(nonewline), _flush(flush) 
        {}

    /*****************************************************************************/

    void _pair_output_functor_t::config(const string& path, 
            const string& dlm, size_t width,
            bool keyfirst, bool nonewline,
            bool flush) noexcept
    {
        _path = path;
        _dlm = dlm;
        _width = width;
        _keyfirst = keyfirst;
        _nonewline = nonewline;
        _flush = flush;
    }

    /*****************************************************************************/

    template<typename KeyType, typename ValType>
        typename enable_if< is_direct_outputable< ValType >::value, 
                 const _pair_output_functor_t&>::type
        _pair_output_functor_t::operator()(const KeyType& key, const ValType& val) const
        {
            iostream& dest = io_base_obj.at(_path);
            if (_keyfirst) 
                dest << setw(_width) << key << _dlm << setw(_width) << val;
            else 
                dest <<  setw(_width) << val << _dlm << setw(_width) << key;
            if (!_nonewline) dest <<  "\n";
            if (_flush) dest << flush;
            return *this;
        }

    /*****************************************************************************/

    template<typename KeyType, typename ValType>
        typename enable_if< is_sequence_container<ValType>::value,
                 const _pair_output_functor_t& >::type
        _pair_output_functor_t::operator()(const KeyType& key, const ValType& val) const
        {
            iostream& dest = io_base_obj.at(_path);
            if(_keyfirst) {
                dest <<  setw(_width) << key << _dlm;
                for(auto& it : val) dest <<  setw(_width) << it;
            }
            else{
                for(auto& it : val) dest <<  setw(_width) << it;
                dest <<  _dlm << setw(_width) << key ;
            }
            if(!_nonewline) dest <<  "\n";
            if (_flush) dest << flush;
            return *this;
        }

    /*****************************************************************************/

};

#endif // _IOER_OUTPUT_T_HPP
