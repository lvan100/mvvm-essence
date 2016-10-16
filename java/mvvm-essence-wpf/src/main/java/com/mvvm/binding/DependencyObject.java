package com.mvvm.binding;

import com.mvvm.model.Model;
import com.mvvm.notify.IPropertyChangedSupport;

import static com.print.PrintHelper.PRINT_HELPER;

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
     * 获取数据绑定对象
     */
    public DataBinding<T> getDataBinding() {
        return dataBinding;
    }

    /**
     * 设置数据绑定对象
     */
    public void setDataBinding(DataBinding<T> dataBinding) {
        this.dataBinding = dataBinding;
    }

    @Override
    public T getValue() {
        PRINT_HELPER.print(this.toString() + ":DependencyObject.getValue");
        if (dataBinding == null) {
            return super.getValue();
        } else {
            return dataBinding.getSourceValue();
        }
    }

    @Override
    public void setValue(T value) {
        PRINT_HELPER.enterPrint(this.toString() + ":DependencyObject.setValue.begin");
        {
            if (dataBinding == null) {
                super.setValue(value);
            } else {
                dataBinding.setSourceValue(value);
            }
        }
        PRINT_HELPER.exitPrint(this.toString() + ":DependencyObject.setValue.end");
    }

    @Override
    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
        PRINT_HELPER.enterPrint(this.toString() + ":DependencyObject.onPropertyChanged");

        PRINT_HELPER.print(this.toString() +
                ":DependencyObject.notifyPropertyChanged.begin");

        // 通知其值已经发生变化
        notifyPropertyChanged(this, valueProperty);

        PRINT_HELPER.exitPrint(this.toString() +
                ":DependencyObject.notifyPropertyChanged.end");
    }

}
