#ifndef MATIOCPP_UTILITIES_H
#define MATIOCPP_UTILITIES_H
/*
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia
 *
 * Licensed under either the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 * or the GNU Lesser General Public License v2.1 :
 * https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
 * at your option.
 */

#include <matioCpp/ForwardDeclarations.h>

namespace matioCpp {

matio_types get_matio_value_type(const ValueType& inputValueType);

bool get_matio_types(const VariableType& inputVariableType, const ValueType& inputValueType, matio_classes& outputMatioClasses, matio_types& outputMatioType);

bool get_types_from_matvart(const matvar_t* input, VariableType& outputVariableType, ValueType &outputValueType);

// defaults
template <typename Tp> struct get_type;
//template <typename Tp> struct cpp_to_matio_class;
// specializations
template <> struct get_type<int8_t>   { using type = int8_t;   static constexpr ValueType valueType = ValueType::INT8; };
template <> struct get_type<uint8_t>  { using type = uint8_t;  static constexpr ValueType valueType = ValueType::UINT8; };
template <> struct get_type<int16_t>  { using type =  int16_t; static constexpr ValueType valueType = ValueType::INT16; };
template <> struct get_type<uint16_t> { using type = uint16_t; static constexpr ValueType valueType = ValueType::UINT16; };
template <> struct get_type<int32_t>  { using type = int32_t;  static constexpr ValueType valueType = ValueType::INT32; };
template <> struct get_type<uint32_t> { using type = uint32_t; static constexpr ValueType valueType = ValueType::UINT32; };
template <> struct get_type<float>    { using type = float;    static constexpr ValueType valueType = ValueType::SINGLE; };
template <> struct get_type<double>   { using type = double;   static constexpr ValueType valueType = ValueType::DOUBLE; };
template <> struct get_type<int64_t>  { using type = int64_t;  static constexpr ValueType valueType = ValueType::INT64; };
template <> struct get_type<char> { using type = char; static constexpr ValueType valueType = ValueType::UTF8; };
template <> struct get_type<char16_t> { using type = char16_t; static constexpr ValueType valueType = ValueType::UTF16; };
template <> struct get_type<char32_t> { using type = char32_t; static constexpr ValueType valueType = ValueType::UTF32; };
template <> struct get_type<std::string> { using type = std::string; static constexpr ValueType valueType = ValueType::STRING; };


// reverse map from id to basic type
template <int matio_type_id = -1> struct matio_type_to_cpp {};
template <> struct matio_type_to_cpp<MAT_T_INT8>   { using type = int8_t; };
template <> struct matio_type_to_cpp<MAT_T_UINT8>  { using type = uint8_t; };
template <> struct matio_type_to_cpp<MAT_T_INT16>  { using type = int16_t; };
template <> struct matio_type_to_cpp<MAT_T_UINT16> { using type = uint16_t; };
template <> struct matio_type_to_cpp<MAT_T_INT32>  { using type = int32_t; };
template <> struct matio_type_to_cpp<MAT_T_UINT32> { using type = uint32_t; };
template <> struct matio_type_to_cpp<MAT_T_SINGLE> { using type = float; };
template <> struct matio_type_to_cpp<MAT_T_DOUBLE> { using type = double; };
template <> struct matio_type_to_cpp<MAT_T_INT64>  { using type = int64_t; };
template <> struct matio_type_to_cpp<MAT_T_UINT64> { using type = uint64_t; };

template <typename T>
bool is_convertible_to_primitive_type(matioCpp::ValueType type)
{
    switch (type)
    {
    case matioCpp::ValueType::INT8:
        return std::is_convertible<T, int8_t>::value;
        break;
    case matioCpp::ValueType::UINT8:
        return std::is_convertible<T, uint8_t>::value;
        break;
    case matioCpp::ValueType::INT16:
        return std::is_convertible<T, int16_t>::value;
        break;
    case matioCpp::ValueType::UINT16:
        return std::is_convertible<T, uint16_t>::value;
        break;
    case matioCpp::ValueType::INT32:
        return std::is_convertible<T, int32_t>::value;
        break;
    case matioCpp::ValueType::UINT32:
        return std::is_convertible<T, uint32_t>::value;
        break;
    case matioCpp::ValueType::SINGLE:
        return std::is_convertible<T, float>::value;
        break;
    case matioCpp::ValueType::DOUBLE:
        return std::is_convertible<T, double>::value;
        break;
    case matioCpp::ValueType::INT64:
        return std::is_convertible<T, int64_t>::value;
        break;
    case matioCpp::ValueType::UINT64:
        return std::is_convertible<T, uint64_t>::value;
        break;
    case matioCpp::ValueType::UTF8:
        return std::is_convertible<T, char>::value;
        break;
    case matioCpp::ValueType::UTF16:
        return std::is_convertible<T, char16_t>::value;
        break;
    case matioCpp::ValueType::UTF32:
        return std::is_convertible<T, char32_t>::value;
        break;
    case matioCpp::ValueType::STRING:
    case matioCpp::ValueType::CELL:
    case matioCpp::ValueType::STRUCT:
    case matioCpp::ValueType::VECTOR:
    case matioCpp::ValueType::MULTI_DIMENSIONAL_ARRAY:
    case matioCpp::ValueType::UNSUPPORTED:
        return false;
    }
    return false;
}


}


#endif //MATIOCPP_UTILITIES_H