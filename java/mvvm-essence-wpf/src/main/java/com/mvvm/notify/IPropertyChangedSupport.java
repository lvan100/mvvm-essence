package com.mvvm.notify;

/**
 * 属性值变化支持接口
 */
public interface IPropertyChangedSupport {

    /**
     * 根据属性名称获取相应的属性值
     *
     * @param propertyName 属性名称
     * @return 返回相应的属性值
     */
    Object getProperty(String propertyName);

    /**
     * 根据属性名称设置相应的属性值
     *
     * @param propertyName 属性名称
     * @param value        属性值
     */
    void setProperty(String propertyName, Object value);

    /**
     * 获取属性值变化处理器
     */
    PropertyChangedHandler getPropertyChangedHandler();

    /**
     * 响应属性值变化事件
     *
     * @param eventSource  属性发生变化的对象，要求实现 IPropertyChangedSupport 接口。
     * @param propertyName 发生变化的属性名称
     */
    default void onPropertyChanged(
            IPropertyChangedSupport eventSource, String propertyName) {
    }

}
