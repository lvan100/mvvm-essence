package com.mvvm.model;

import com.mvvm.binding.DataBinding;
import com.mvvm.notify.IPropertyChangedSupport;
import com.mvvm.notify.PropertyChangedHandler;

import java.util.Objects;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 依赖对象
 */
public final class DependencyObject<T> implements IPropertyChangedSupport {

    /**
     * 客户端值
     */
    private T value;

    /**
     * 是否只能读取
     */
    private boolean readOnly;

    /**
     * 数据绑定对象
     */
    private DataBinding<T> dataBinding;

    /**
     * 客户端值的属性名称
     */
    public static final String valueProperty = "value";

    public DependencyObject(T value) {
        this.value = value;
    }

    public DependencyObject(boolean readOnly, T value) {
        this.readOnly = readOnly;
        this.value = value;
    }

    public T getValue() {
        PRINT_HELPER.print(this.toString() + ":DependencyObject.getValue");
        if (dataBinding == null) {
            return value;
        } else {
            return dataBinding.getSourceValue();
        }
    }

    public void setValue(T value) {
        if (dataBinding == null) {
            if (!isReadOnly()) {

                PRINT_HELPER.enterPrint(this.toString() + ":DependencyObject.setValue.begin");
                {
                    PRINT_HELPER.print(this.toString() + ":DependencyObject.setValue="
                            + this.value + "->" + value);

                    if (Objects.deepEquals(this.value, value)) {
                        PRINT_HELPER.exit();
                        PRINT_HELPER.exitPrint(this.toString() + ":DependencyObject.setValue.end");

                    } else {
                        this.value = value;

                        PRINT_HELPER.exit();
                        PRINT_HELPER.exitPrint(this.toString() + ":DependencyObject.setValue.end");

                        PRINT_HELPER.enterPrint(this.toString()
                                + ":DependencyObject.notifyPropertyChanged.begin");
                        {
                            handler.notifyPropertyChanged(this, valueProperty);
                        }
                        PRINT_HELPER.exitPrint(this.toString()
                                + ":DependencyObject.notifyPropertyChanged.end");
                    }
                }
            }
        } else {
            PRINT_HELPER.enterPrint(this.toString() + ":DependencyObject.setValue.begin");
            {
                dataBinding.setSourceValue(value);
            }
            PRINT_HELPER.exitPrint(this.toString() + ":DependencyObject.setValue.end");
        }
    }

    public boolean isReadOnly() {
        return readOnly;
    }

    public void setReadOnly(boolean readOnly) {
        this.readOnly = readOnly;
    }

    @Override
    public Object getProperty(String propertyName) {
        PRINT_HELPER.print(this.toString() + ":DependencyObject.getProperty[\"" + propertyName + "\"]");
        return getValue();
    }

    @Override
    public void setProperty(String propertyName, Object value) {
        PRINT_HELPER.print(this.toString() + ":DependencyObject.setProperty[\"" + propertyName + "\"]");
        setValue((T) value);
    }

    /**
     * 获取数据绑定对象
     */
    public DataBinding<T> getDataBinding() {
        return dataBinding;
    }

    /**
     * 设置数据绑定对象
     */
    public void setDataBinding(DataBinding<T> dataBinding) {
        IPropertyChangedSupport dataSource = dataBinding.getSource();
        String propertyName = dataBinding.getSourcePropertyName();

        this.dataBinding = dataBinding;
        dataBinding.setTarget(this);

        dataSource.getPropertyChangedHandler().addPropertyChangedNotify(
                propertyName, this);

        PRINT_HELPER.enterPrint(dataSource.toString() +
                ":notifyValueChanged.begin");
        {
            dataSource.getPropertyChangedHandler()
                    .notifyPropertyChanged(dataSource, propertyName);
        }
        PRINT_HELPER.exitPrint(dataSource.toString() +
                ":notifyValueChanged.end");
    }

    /**
     * 属性值变化通知管理器
     */
    private final PropertyChangedHandler handler = new PropertyChangedHandler();

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return handler;
    }

    @Override
    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
        PRINT_HELPER.enterPrint(this.toString() + ":DependencyObject.onPropertyChanged");

        PRINT_HELPER.print(this.toString() +
                ":DependencyObject.notifyPropertyChanged.begin");
        {
            handler.notifyPropertyChanged(this, valueProperty);
        }
        PRINT_HELPER.exitPrint(this.toString() +
                ":DependencyObject.notifyPropertyChanged.end");
    }

}
