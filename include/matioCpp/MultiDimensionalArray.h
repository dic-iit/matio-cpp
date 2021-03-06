#ifndef MATIOCPP_MULTIDIMENSIONALARRAY_H
#define MATIOCPP_MULTIDIMENSIONALARRAY_H

/*
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia
 *
 * This software may be modified and distributed under the terms of the
 * BSD-2-Clause license (https://opensource.org/licenses/BSD-2-Clause).
 */

#include <matioCpp/ForwardDeclarations.h>
#include <matioCpp/ConversionUtilities.h>
#include <matioCpp/Span.h>
#include <matioCpp/Variable.h>

/**
 * @brief MultiDimensionalArray is a particular type of Variable specialized for multidimensional arrays of a generic type T.
 * @note The underlying array is in column-major format.
 */
template<typename T>
class matioCpp::MultiDimensionalArray : public matioCpp::Variable
{

    /**
     * @brief Check if an input matio pointer is compatible with the MultiDimensionalArray class.
     * @param inputPtr The input matvar_t pointer.
     * @param variableType The type of variable.
     * @param valueType The value type.
     * @return True if compatible. False otherwise, throwing errors.
     */
    virtual bool checkCompatibility(const matvar_t* inputPtr, matioCpp::VariableType variableType, matioCpp::ValueType valueType) const final;

public:

    using type = T; /** Defines the type specified in the template. **/

    using element_type = typename get_type<T>::type; /** Defines the type of an element of the MultiDimensionalArray. **/

    using value_type = std::remove_cv_t<element_type>; /** Defines the type of an element of the MultiDimensionalArray without "const". Useful to use make_span. **/

    using allocator_type = std::allocator<element_type>; /** Defines how to allocate T. **/

    using index_type = size_t; /** The type used for indices. **/

    using reference = element_type&; /** The reference type. **/

    using pointer = typename std::allocator_traits<std::allocator<element_type>>::pointer; /** The pointer type. **/

    using const_pointer = typename std::allocator_traits<std::allocator<element_type>>::const_pointer; /** The const pointer type. **/

    /**
     * @brief Default Constructor
     * @note The name is set to "unnamed_multidimensional_array".
     */
    MultiDimensionalArray();

    /**
     * @brief Constructor
     * @param name The name of the MultiDimensionalArray
     */
    MultiDimensionalArray(const std::string& name);

    /**
     * @brief Constructor
     * @param name The name of the MultiDimensionalArray
     * @param dimensions The dimensions of the MultiDimensionalArray
     */
    MultiDimensionalArray(const std::string& name, const std::vector<index_type>& dimensions);

    /**
     * @brief Constructor
     * @param name The name of the MultiDimensionalArray
     * @param dimensions The dimensions of the MultiDimensionalArray
     * @param inputVector The raw pointer to the data stored in column-major order
     */
    MultiDimensionalArray(const std::string& name, const std::vector<index_type>& dimensions, const_pointer inputVector);

    /**
     * @brief Copy constructor
     */
    MultiDimensionalArray(const MultiDimensionalArray<T>& other);

    /**
     * @brief Move constructor
     */
    MultiDimensionalArray(MultiDimensionalArray<T>&& other);

    /**
     * @brief Constructor to share the data ownership of another variable.
     * @param handler The MatvarHandler handler to the matvar_t which has to be shared.
     */
    MultiDimensionalArray(const MatvarHandler& handler);

    /**
    * Destructor.
    */
    ~MultiDimensionalArray();

    /**
     * @brief Assignement operator (copy) from another MultiDimensionalArray.
     * @param other The other MultiDimensionalArray.
     * @note Also the name is copied
     * @return A reference to this MultiDimensionalArray.
     */
    MultiDimensionalArray<T>& operator=(const MultiDimensionalArray<T>& other);

    /**
     * @brief Assignement operator (move) from another MultiDimensionalArray.
     * @param other The other MultiDimensionalArray.
     * @note Also the name is copied
     * @return A reference to this MultiDimensionalArray.
     */
    MultiDimensionalArray<T>& operator=(MultiDimensionalArray<T>&& other);

    /**
     * @brief Set from a vectorized array
     * @note The pointer is supposed to be in column-major format.
     * @param dimensions The input dimensions
     * @param inputVector The input pointer.
     * @return True if successful.
     */
    bool fromVectorizedArray(const std::vector<index_type>& dimensions, const_pointer inputVector);

    /**
     * @brief Get the index in the vectorized array corresponding to the provided indices
     * @param el The desired element
     * @warning It checks if the element is in the bounds only in debug mode.
     *
     * Since the array is stored in column-major, an element (i,j,k,l,..) of an array
     * of dimensions (n,m,p,k,...) corresponds to a row index
     * equal to i + j*n + k*n*m + l*n*m*p +...
     *
     * @return the index in the vectorized array corresponding to the provided indices
     */
    index_type rawIndexFromIndices(const std::vector<index_type>& el) const;

    /**
     * @brief Get the indices given the raw index
     * @param rawIndex The input raw index from which to compute the indices
     * @param el The output indices

    * @return True if successful, false otherwise (for example if rawIndex is out of bounds)
     */
    bool indicesFromRawIndex(size_t rawIndex, std::vector<index_type>& el) const;

    /**
     * @brief Get this MultiDimensionalArray as a Span
     */
    matioCpp::Span<element_type> toSpan();

    /**
     * @brief Get this MultiDimensionalArray as a Span (const version)
     */
    const matioCpp::Span<const element_type> toSpan() const;

    /**
     * @brief Change the name of the Variable
     * @param newName The new name
     * @return True if successful.
     */
    bool setName(const std::string& newName);

    /**
     * @brief Resize the vector.
     * @param newDimensions The new dimensions.
     *
     * @warning Previous data is lost.
     */
    void resize(const std::vector<index_type>& newDimensions);

    /**
     * @brief Clear the multidimensional array
     */
    void clear();

    /**
     * @brief Direct access to the underlying array.
     * @note The underlying array is in column-major format.
     * @return A pointer to the internal data.
     */
    pointer data();

    /**
     * @brief Direct access to the underlying array.
     * @note The underlying array is in column-major format.
     * @return A pointer to the internal data.
     */
    const_pointer data() const;

    /**
     * @brief Get the total number of elements in the array
     * @return The total number of elements
     */
    index_type numberOfElements() const;

    /**
     * @brief Access specified element.
     * @param el The element to be accessed.
     * @warning Each element of el has to be strictly smaller than the corresponding dimension.
     * @return A reference to the element.
     */
    reference operator()(const std::vector<index_type>& el);

    /**
     * @brief Access specified element.
     * @param el The element to be accessed.
     * @warning Each element of el has to be strictly smaller than the corresponding dimension.
     * @return A copy to the element.
     */
    value_type operator()(const std::vector<index_type>& el) const;

    /**
     * @brief Access specified element.
     * @param el The element to be accessed (raw index).
     * @return A reference to the element.
     */
    reference operator()(index_type el);

    /**
     * @brief Access specified element.
     * @param el The element to be accessed (raw index).
     * @return A copy to the element.
     */
    value_type operator()(index_type el) const;

    /**
     * @brief Access specified element.
     * @param el The element to be accessed.
     * @warning Each element of el has to be strictly smaller than the corresponding dimension.
     * @return A reference to the element.
     */
    reference operator[](const std::vector<index_type>& el);

    /**
     * @brief Access specified element.
     * @param el The element to be accessed.
     * @warning Each element of el has to be strictly smaller than the corresponding dimension.
     * @return A copy to the element.
     */
    value_type operator[](const std::vector<index_type>& el) const;

    /**
     * @brief Access specified element.
     * @param el The element to be accessed (raw index).
     * @return A reference to the element.
     */
    reference operator[](index_type el);

    /**
     * @brief Access specified element.
     * @param el The element to be accessed (raw index).
     * @return A copy to the element.
     */
    value_type operator[](index_type el) const;
};

#include "impl/MultiDimensionalArray.tpp"

#endif // MATIOCPP_MULTIDIMENSIONALARRAY_H
