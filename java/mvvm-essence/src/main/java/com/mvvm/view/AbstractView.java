package com.mvvm.view;

import com.mvvm.binding.DataBinding;

/**
 * 抽象视图控件，实现了一些View的接口方法。
 */
public abstract class AbstractView implements View {

    private String id;

    @Override
    public String getId() {
        return id;
    }

    @Override
    public void setId(String id) {
        this.id = id;
    }

    @Override
    public void setDataBinding(String propertyName, DataBinding<?> binding) {
    }

}
