/**
 * @file   exceptions.hpp
 * @author nullkal <nullkal@nil.nu>
 *
 * @brief  declares various exceptions used widely in this library.
 */

/*
 * Copyright (c) 2016 nullkal <nullkal@nil.nu>
 *
 * This file is distributed under the MIT License.
 * See LICENSE for more information.
 */

#ifndef OPENGL_COMMON_EXCEPTIONS_HPP
#define OPENGL_COMMON_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace kal {
namespace gl {

/**
 * @brief The exception thrown when the file operation is failed.
 */
class FileException: public std::exception {
public:
    /**
     * @brief The constructor.
     * @param[in] message  The error message.
     */
    explicit FileException(const char* const message):
        std::exception(),
        m_message(message)
    {}

    /**
     * @brief Return the error message.
     * @return The error message.
     */
    const char* what() const
    {
        return m_message.c_str();
    }

private:
    std::string m_message; /**< The error message. */
};

}} // kal::gl

#endif//OPENGL_COMMON_EXCEPTIONS_HPP
