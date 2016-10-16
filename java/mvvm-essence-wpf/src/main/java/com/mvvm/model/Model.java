package com.mvvm.model;

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
        PRINT_HELPER.print(this.toString() + ":Model.getValue=" + value);
        return value;
    }

    @Override
    public void setValue(T value) {
        if (!isReadOnly()) {

            PRINT_HELPER.print(this.toString() + ":Model.setValue="
                    + this.value + "->" + value);
            this.value = value;

            PRINT_HELPER.enterPrint(this.toString()
                    + ":Model.notifyPropertyChanged.begin");

            // 通知其值已经发生变化
            notifyPropertyChanged(this, valueProperty);

            PRINT_HELPER.exitPrint(this.toString()
                    + ":Model.notifyPropertyChanged.end");
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
    }

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return this;
    }

}
