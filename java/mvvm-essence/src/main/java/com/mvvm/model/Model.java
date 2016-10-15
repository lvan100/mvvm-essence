package com.mvvm.model;

import com.mvvm.notify.IPropertyChangedSupport;
import com.mvvm.notify.PropertyChangedHandler;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 数据模型的实现
 */
public class Model<T> extends PropertyChangedHandler implements ModelInterface<T> {

    /**
     * 客户端值
     */
    private T value;

    /**
     * 是否只能读取
     */
    private boolean readOnly = false;

    /**
     * 客户端值的属性名称
     */
    public static final String valueProperty = "value";

    public Model(T value) {
        this.value = value;
    }

    public Model(boolean readOnly, T value) {
        this.readOnly = readOnly;
        this.value = value;
    }

    @Override
    public T getValue() {
        System.out.println(this.toString() + ":Model.getValue=" + value);
        return value;
    }

    @Override
    public void setValue(T value) {
        if (!isReadOnly()) {

            System.out.println(this.toString() + ":Model.setValue="
                    + this.value + "->" + value);
            this.value = value;

            System.out.println(this.toString()
                    + ":Model.notifyPropertyChanged");

            // 通知其值已经发生变化
            notifyPropertyChanged(null, this, valueProperty);
        }
    }

    @Override
    public boolean isReadOnly() {
        return readOnly;
    }

    @Override
    public void setReadOnly(boolean readOnly) {
        this.readOnly = readOnly;
    }

    @Override
    public Object getProperty(String propertyName) {
        PRINT_HELPER.print(this.toString() + ":Model.getProperty[\"" + propertyName + "\"]");
        if (valueProperty.equals(propertyName)) {
            return getValue(); // 子类可能会覆盖 getValue() 函数
        }
        return null;
    }

    @Override
    public void setProperty(String propertyName, Object value) {
        PRINT_HELPER.print(this.toString() + ":Model.setProperty[\"" + propertyName + "\"]");
        if (valueProperty.equals(propertyName)) {
            setValue((T) value);
        }
    }

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return this;
    }

    @Override
    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
        System.out.println(this.toString() + ":Model.onPropertyChanged");
        if (!isReadOnly()) {

            T newValue = (T) eventSource.getProperty(propertyName);
            System.out.println(this.toString() + ":Model.value="
                    + this.value + "->" + newValue);
            this.value = newValue;

            System.out.println(this.toString()
                    + ":Model.notifyPropertyChanged");

            // 通知其值已经发生变化
            notifyPropertyChanged(eventSource, this, valueProperty);
        }
    }

}
