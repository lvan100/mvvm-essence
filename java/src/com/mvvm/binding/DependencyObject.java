package com.mvvm.binding;

import com.mvvm.model.Model;
import com.mvvm.notify.IPropertyChangedSupport;

/**
 * 依赖对象，数据模型+数据绑定，绑定后通过绑定获取真正的值。
 *
 * @param <T>
 */
public class DependencyObject<T> extends Model<T> {

    /**
     * 数据绑定对象
     */
    private DataBinding<T> dataBinding;

    public DependencyObject(T value) {
        super(value);
    }

    public DependencyObject(boolean readOnly, T value) {
        super(readOnly, value);
    }

    /**
     * 设置数据绑定对象
     */
    public void setDataBinding(DataBinding<T> dataBinding) {
        this.dataBinding = dataBinding;
    }

    @Override
    public T getValue() {
        System.out.println(this.toString() + ":DependencyObject.getValue");
        if (dataBinding == null) {
            return super.getValue();
        } else {
            return dataBinding.getSourceValue();
        }
    }

    @Override
    public void setValue(T value) {
        System.out.println(this.toString() + ":DependencyObject.setValue");

        if (dataBinding == null) {
            super.setValue(value);
        } else {
            dataBinding.setSourceValue(value);
        }
    }

    @Override
    public void setProperty(String propertyName, Object value) {
        System.out.println(this.toString() + ":DependencyObject.setProperty[\"" + propertyName + "\"]");
        if (dataBinding == null) {
            super.setProperty(propertyName, value);

        } else {
            if (valueProperty.equals(propertyName)) {
                dataBinding.setSourceValue((T) value);
            }
        }
    }

    @Override
    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
        System.out.println(this.toString() + ":DependencyObject.onPropertyChanged");
        if (dataBinding == null) {
            super.onPropertyChanged(eventSource, propertyName);

        } else {

            System.out.println(this.toString() +
                    ":DependencyObject.notifyPropertyChanged");

            // 通知其值已经发生变化
            notifyPropertyChanged(eventSource, this, valueProperty);
        }
    }

}
