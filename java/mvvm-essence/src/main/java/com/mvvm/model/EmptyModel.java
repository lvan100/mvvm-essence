package com.mvvm.model;

/**
 * 没有值的数据模型，主要用于Model向View传递界面更新事件。
 */
public abstract class EmptyModel<T> implements BindableModel<T> {

    @Override
    public T getValue() {
        return null;
    }

    @Override
    public void setValue(Object value) {
    }

    @Override
    public void bindModel(BindableModel model) {
    }

    @Override
    public void unbindModel(BindableModel model) {
    }

}
