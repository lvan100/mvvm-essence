package com.mvvm.model;

import com.mvvm.binding.DataBinding;

import java.util.ArrayList;
import java.util.List;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 标准数据模型
 */
public final class Model<T> implements INotifyValueChanged {

    /**
     * 客户端值
     */
    private T value;

    /**
     * 是否只读
     */
    private boolean readOnly;

    /**
     * 数据绑定对象
     */
    private DataBinding<T> dataBinding;

    public Model(T value) {
        this.value = value;
    }

    public Model(boolean readOnly, T value) {
        this.readOnly = readOnly;
        this.value = value;
    }

    /**
     * 获取数据模型的值
     */
    public T getValue() {
        PRINT_HELPER.print(this.toString() + ":Model.getValue");
        if (dataBinding == null) {
            return value;
        } else {
            return dataBinding.getSourceValue();
        }
    }

    /**
     * 设置数据模型的值
     */
    public void setValue(T value) {
        if (dataBinding == null) {
            if (!isReadOnly()) {

                PRINT_HELPER.enterPrint(this.toString() + ":Model.setValue.begin");
                {
                    PRINT_HELPER.enterPrint(this.toString() + ":Model.setValue="
                            + this.value + "->" + value);
                    this.value = value;
                    PRINT_HELPER.exit();
                }
                PRINT_HELPER.exitPrint(this.toString() + ":Model.setValue.end");

                PRINT_HELPER.enterPrint(this.toString()
                        + ":Model.notifyValueChanged.begin");
                {
                    notifyValueChanged();
                }
                PRINT_HELPER.exitPrint(this.toString()
                        + ":Model.notifyValueChanged.end");
            }

        } else {
            PRINT_HELPER.enterPrint(this.toString() + ":Model.setValue.begin");
            {
                dataBinding.setSourceValue(value);
            }
            PRINT_HELPER.exitPrint(this.toString() + ":Model.setValue.end");
        }
    }

    /**
     * 数据模型是否只读
     */
    public boolean isReadOnly() {
        return readOnly;
    }

    /**
     * 设置数据模型是否只读
     */
    public void setReadOnly(boolean readOnly) {
        this.readOnly = readOnly;
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

        Model dataSource = dataBinding.getSource();
        dataSource.addNotifyValueChanged(this);

        this.dataBinding = dataBinding;
        dataBinding.setTarget(this);

        PRINT_HELPER.enterPrint(dataSource.toString() +
                ":notifyValueChanged.begin");
        {
            dataSource.notifyValueChanged();
        }
        PRINT_HELPER.exitPrint(dataSource.toString() +
                ":notifyValueChanged.end");
    }

    @Override
    public void onValueChanged(Model model) {
        PRINT_HELPER.enterPrint(this.toString() + ":Model.onValueChanged");

        PRINT_HELPER.print(this.toString() +
                ":Model.notifyValueChanged.begin");
        {
            notifyValueChanged();
        }
        PRINT_HELPER.exitPrint(this.toString() +
                ":Model.notifyValueChanged.end");
    }

    /**
     * 数据模型值变化通知列表
     */
    private final List<INotifyValueChanged> notifyList = new ArrayList<>();

    /**
     * 添加值变化通知对象
     */
    public void addNotifyValueChanged(INotifyValueChanged notify) {
        notifyList.add(notify);
    }

    /**
     * 移除值变化通知对象
     */
    public void removeNotifyValueChanged(INotifyValueChanged notify) {
        notifyList.remove(notify);
    }

    /**
     * 通知数据模型的值变化事件
     */
    private void notifyValueChanged() {
        for (INotifyValueChanged notify : notifyList) {
            PRINT_HELPER.enterPrint(notify.toString() +
                    ":Model.onValueChanged.begin");
            {
                notify.onValueChanged(this);
            }
            PRINT_HELPER.exitPrint(notify.toString() +
                    ":Model.onValueChanged.end");
        }
    }

}
