package com.mvvm.model;

import com.mvvm.binding.DataBinding;

import java.util.ArrayList;
import java.util.List;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 标准数据模型
 */
public class Model<T> implements BindableModel<T> {

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

    public Model(T value) {
        this.value = value;
    }

    public Model(boolean readOnly, T value) {
        this.readOnly = readOnly;
        this.value = value;
    }

    @Override
    public T getValue() {
        PRINT_HELPER.print(this.toString() + ":Model.getValue");
        if (dataBinding == null) {
            return value;
        } else {
            return dataBinding.getSourceValue();
        }
    }

    @Override
    public void setValue(Object value) {
        PRINT_HELPER.enterPrint(this.toString() + ":Model.setValue.begin");
        {
            if (dataBinding == null) {
                if (!isReadOnly()) {

                    PRINT_HELPER.print(this.toString() + ":Model.setValue="
                            + this.value + "->" + value);
                    this.value = (T) value;

                    PRINT_HELPER.enterPrint(this.toString()
                            + ":Model.notifyModelChanged.begin");

                    // 通知其值已经发生变化
                    notifyModelChanged(null, this);

                    PRINT_HELPER.exitPrint(this.toString()
                            + ":Model.notifyModelChanged.end");
                }

            } else {
                dataBinding.setSourceValue((T) value);
            }
        }
        PRINT_HELPER.exitPrint(this.toString() + ":Model.setValue.end");
    }

    public boolean isReadOnly() {
        return readOnly;
    }

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
        this.dataBinding = dataBinding;
        dataBinding.setTarget(this);
        dataBinding.build();
    }

    /**
     * 已绑定的数据模型列表
     */
    private List<BindableModel> bondedModelList = new ArrayList<>();

    @Override
    public void bindModel(BindableModel model) {
        bondedModelList.add(model);
    }

    @Override
    public void unbindModel(BindableModel model) {
        bondedModelList.remove(model);
    }

    @Override
    public void onValueChanged(BindableModel source) {
        PRINT_HELPER.enterPrint(this.toString() + ":Model.onValueChanged");

        if (dataBinding == null) {
            if (!isReadOnly()) {
                T newValue = dataBinding.getSourceValue();
                PRINT_HELPER.print(this.toString() + ":Model.value="
                        + this.value + "->" + newValue);
                this.value = newValue;
            }
        }

        PRINT_HELPER.print(this.toString() +
                ":Model.notifyModelChanged.begin");

        // 通知其值已经发生变化
        notifyModelChanged(source, this);

        PRINT_HELPER.exitPrint(this.toString() +
                ":Model.notifyModelChanged.end");
    }

    /**
     * 通知数据模型的值变化事件
     */
    public void notifyModelChanged(BindableModel exclude, BindableModel source) {
        for (BindableModel model : bondedModelList) {
            PRINT_HELPER.enterPrint(model.toString() +
                    ":Model.onValueChanged.begin");
            {
                if (model != exclude) {
                    model.onValueChanged(source);

                } else {
                    PRINT_HELPER.enterPrint(model.toString() +
                            ":Model.onValueChanged.skip");
                    PRINT_HELPER.exit();
                }
            }
            PRINT_HELPER.exitPrint(model.toString() +
                    ":Model.onValueChanged.end");
        }
    }

}
