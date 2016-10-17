package com.mvvm.binding;

import com.mvvm.model.Model;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 数据绑定
 */
public class DataBinding<T> {

    /**
     * 源绑定对象
     */
    private Model source;

    /**
     * 目标绑定对象
     */
    private Model<T> target;

    /**
     * 数据绑定的类型
     */
    private BindingType type = BindingType.TwoWay;

    public DataBinding(BindingType type) {
        this.type = type;
    }

    public DataBinding(BindingType type, Model source) {
        this.source = source;
        this.type = type;
    }

    public BindingType getType() {
        return type;
    }

    public void setType(BindingType type) {
        this.type = type;
    }

    public Model getSource() {
        return source;
    }

    public void setSource(Model source) {
        this.source = source;
    }

    public Model<T> getTarget() {
        return target;
    }

    public void setTarget(Model<T> target) {
        this.target = target;
    }

    /**
     * 值转换器
     */
    private ValueConverter<T> converter = new ValueConverter<T>() {
    };

    /**
     * 设置值转换器
     */
    public void setValueConverter(ValueConverter<T> converter) {
        this.converter = converter;
    }

    /**
     * 获取源绑定对象的值
     */
    public T getSourceValue() {
        PRINT_HELPER.print(this.toString() + ":getSourceValue");
        return converter.convert(source.getValue());
    }

    /**
     * 设置源绑定对象的值
     */
    public void setSourceValue(T newValue) {
        PRINT_HELPER.enterPrint(this.toString() + ":setSourceValue.begin");
        {
            if (getType() == BindingType.TwoWay) {
                source.setValue(converter.reverseConvert(newValue));
            }
        }
        PRINT_HELPER.exitPrint(this.toString() + ":setSourceValue.end");
    }

    @Override
    public String toString() {
        return "DataBinding:" + source.toString() + "->" + target.toString();
    }

}
