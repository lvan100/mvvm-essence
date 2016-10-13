package com.mvvm.binding;

import com.mvvm.model.Model;
import com.mvvm.notify.NotifyValueChanged;

/**
 * 数据绑定的实现。
 */
public class DataBinding<T> extends NotifyValueChanged<T> implements DataBindingInterface<T> {

    private Model<T> source;
    private Model<T> target;

    private BindingType type;

    public DataBinding(BindingType type) {
        this.type = type;
    }

    public DataBinding(BindingType type, Model<T> source) {
        this.source = source;
        this.type = type;
    }

    @Override
    public BindingType getType() {
        return type;
    }

    @Override
    public DataBindingInterface<T> setType(BindingType type) {
        this.type = type;
        return this;
    }

    @Override
    public void setTargetValue(T value) {
        System.out.println(source.toString() + "->" + target.toString() +
                ":DataBinding.setTargetValue");
        try {
            target.setValue(value);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void setSourceValue(T value) throws IllegalAccessException {
        System.out.println(source.toString() + "->" + target.toString() +
                ":DataBinding.setSourceValue");

        if (getType() == BindingType.OneWay) {
            throw new IllegalAccessException();
        }

        source.setValue(value);
        notifyValueChanged(value);
    }

    @Override
    public Model<T> getSource() {
        return source;
    }

    @Override
    public DataBindingInterface<T> setSource(Model<T> source) {
        this.source = source;
        return this;
    }

    @Override
    public Model<T> getTarget() {
        return target;
    }

    @Override
    public DataBindingInterface<T> setTarget(Model<T> target) {
        this.target = target;
        return this;
    }

}
