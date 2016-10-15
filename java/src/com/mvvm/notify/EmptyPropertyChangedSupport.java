package com.mvvm.notify;

/**
 * 没有属性的 IPropertyChangedSupport 接口抽象类
 */
public abstract class EmptyPropertyChangedSupport implements IPropertyChangedSupport {

    @Override
    public Object getProperty(String propertyName) {
        return null;
    }

    @Override
    public void setProperty(String propertyName, Object value) {
    }

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return null;
    }

}
