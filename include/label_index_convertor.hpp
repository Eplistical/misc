#ifndef _LABEL_INDEX_CONVERTER_HPP
#define _LABEL_INDEX_CONVERTER_HPP
/* class to convert between label indice (vector) and number index (scalar)
*/
#include <vector>
#include <stdexcept>
#include "types.hpp"
#include "crasher.hpp"

namespace misc {

	template <typename EleType>
		class LabelIndexConverter {
			public:
				LabelIndexConverter() noexcept
				{
				}

				LabelIndexConverter(const std::vector<EleType>& N_per_row) noexcept
				{
					init(N_per_row);
				}
				~LabelIndexConverter() noexcept = default;

			public:
				VOID_T init(const std::vector<EleType>& N_per_row) noexcept
				{
					dim_ = N_per_row.size();
					N_per_row_ = N_per_row;

					factors.clear();
					factors.reserve(dim_);
					EleType tmp(1);
					for (EleType i(0); i < dim_; ++i) {
						factors.push_back(tmp);
						tmp *= N_per_row.at(i);
					}
					maxindex_ = tmp;
				}

			public:
				EleType get_dim() const noexcept { return dim_; }
				std::vector<EleType> get_N_per_row() const noexcept { return N_per_row_; }

			public:
				EleType label_to_index(const std::vector<EleType>& label) const {
					EleType index(0);
					for (EleType i(0); i < dim_; ++i) {
						crasher::confirm<std::out_of_range>(label[i] < N_per_row_[i], "label_to_index: label outflow");
						index += label[i] * factors[i];
					}
					return index;
				}

				std::vector<EleType> index_to_label(EleType index) const {
					crasher::confirm<std::out_of_range>(index < maxindex_, "index_to_label: index outflow");
					std::vector<EleType> label(dim_);
					for (EleType i(dim_ - 1); i >= 0; --i) {
						label[i] = index / factors[i];
						index %= factors[i];
					}
					return label;
				}

			private:
				EleType dim_;
				std::vector<EleType> N_per_row_;
				std::vector<EleType> factors;
				EleType maxindex_;
		};

};

#endif // _LABEL_INDEX_CONVERTER_HPP
