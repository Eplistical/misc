#ifndef _LABEL_INDEX_CONVERTER_HPP
#define _LABEL_INDEX_CONVERTER_HPP
/* class to convert between label indice (vector) and number index (scalar)
*/
#include <cassert>
#include <vector>
#include "types.hpp"

namespace misc {

    class LabelIndexConverter {
        public:
            LabelIndexConverter() noexcept
            {
            }

            LabelIndexConverter(const std::vector<INT_T>& N_per_row) noexcept
            {
                init(N_per_row);
            }
            ~LabelIndexConverter() noexcept = default;

        public:
            VOID_T init(const std::vector<INT_T>& N_per_row) noexcept
            {
                dim_ = N_per_row.size();
                N_per_row_ = N_per_row;

                factors.clear();
                factors.reserve(dim_);
                INT_T tmp(1);
                for (INT_T i(0); i < dim_; ++i) {
                    factors.push_back(tmp);
                    tmp *= N_per_row.at(i);
                }
                maxindex_ = tmp;
            }

        public:
            INT_T get_dim() const noexcept { return dim_; }
            std::vector<INT_T> get_N_per_row() const noexcept { return N_per_row_; }

        public:
            INT_T label_to_index(const std::vector<INT_T>& label) const {
                INT_T index(0);
                for (INT_T i(0); i < dim_; ++i) {
                    assert(label[i] < N_per_row_[i]);
                    index += label[i] * factors[i];
                }
                return index;
            }

            std::vector<INT_T> index_to_label(INT_T index) const {
                assert(index < maxindex_);
                std::vector<INT_T> label(dim_);
                for (INT_T i(dim_ - 1); i >= 0; --i) {
                    label[i] = index / factors[i];
                    index %= factors[i];
                }
                return label;
            }

        private:
            INT_T dim_;
            std::vector<INT_T> N_per_row_;
            std::vector<INT_T> factors;
            INT_T maxindex_;
    };

};

#endif // _LABEL_INDEX_CONVERTER_HPP
