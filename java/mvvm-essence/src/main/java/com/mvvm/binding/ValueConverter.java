package com.mvvm.binding;

/**
 * 值转换器
 */
public interface ValueConverter<T> {

    T convert(Object value);

}
