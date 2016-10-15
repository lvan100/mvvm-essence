package com.mvvm.binding;

/**
 * 值转换器
 */
public interface ValueConverter<T> {

    /**
     * 正向转换，Source -> Target
     */
    default T convert(Object value) {
        return (T) value;
    }

    /**
     * 反向转换，Target -> Source
     */
    default Object reverseConvert(T value) {
        return value;
    }

}
