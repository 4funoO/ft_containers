/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doreshev <doreshev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:51:25 by doreshev          #+#    #+#             */
/*   Updated: 2022/10/19 13:57:39 by doreshev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft {
	//ENABLE IF
	template<bool B, class T = void>
	struct enable_if { };

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	//IS INTEGRAL
	template <class T, T val>
	struct integral_constant {
		typedef integral_constant<T, val>	type;
		typedef T							value_type;

		static const T						value = val;
		operator value_type() const { return value; }
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T>
	struct is_integral : public false_type { };

	template <>
	struct is_integral<bool> : public true_type { };

	template <>
	struct is_integral<char> : public true_type { };

	template <>
	struct is_integral<wchar_t> : public true_type { };

	template <>
	struct is_integral<signed char> : public true_type { };

	template <>
	struct is_integral<short int> : public true_type { };

	template <>
	struct is_integral<int> : public true_type { };

	template <>
	struct is_integral<long int> : public true_type { };

	template <>
	struct is_integral<long long int> : public true_type { };

	template <>
	struct is_integral<unsigned char> : public true_type { };

	template <>
	struct is_integral<unsigned short int> : public true_type { };

	template <>
	struct is_integral<unsigned int> : public true_type { };

	template <>
	struct is_integral<unsigned long int> : public true_type { };

	template <>
	struct is_integral<unsigned long long int> : public true_type { };
}

#endif