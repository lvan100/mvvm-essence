package com.mvvm.binding;

import com.mvvm.model.DependencyObject;
import com.mvvm.notify.IPropertyChangedSupport;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 数据绑定的实现。
 *
 * @param <T>
 */
public class DataBinding<T> {

    /**
     * 绑定类型
     */
    private BindingType type;

    /**
     * 目标绑定对象
     */
    private DependencyObject<T> target;

    /**
     * 源绑定对象及其绑定属性
     */
    private String sourcePropertyName;
    private IPropertyChangedSupport source;

    public DataBinding(BindingType type) {
        this.type = type;
    }

    public DataBinding(BindingType type, DependencyObject source) {
        this.sourcePropertyName = DependencyObject.valueProperty;
        this.source = source;
        this.type = type;
    }

    public DataBinding(BindingType type, IPropertyChangedSupport source, String sourcePropertyName) {
        this.sourcePropertyName = sourcePropertyName;
        this.source = source;
        this.type = type;
    }

    public BindingType getType() {
        return type;
    }

    public void setType(BindingType type) {
        this.type = type;
    }

    public IPropertyChangedSupport getSource() {
        return source;
    }

    public void setSource(IPropertyChangedSupport source) {
        this.source = source;
    }

    public String getSourcePropertyName() {
        return sourcePropertyName;
    }

    public void setSourcePropertyName(String propertyName) {
        this.sourcePropertyName = propertyName;
    }

    public DependencyObject<T> getTarget() {
        return target;
    }

    public void setTarget(DependencyObject<T> target) {
        this.target = target;
    }

    /**
     * 值转换器
     */
    private ValueConverter<T> converter = new ValueConverter<T>() {
    };

    public void setValueConverter(ValueConverter<T> converter) {
        this.converter = converter;
    }

    /**
     * 获取源绑定对象的属性值
     */
    public T getSourceValue() {
        PRINT_HELPER.print(this.toString() + ":getSourceValue");
        return converter.convert(source.getProperty(sourcePropertyName));
    }

    /**
     * 设置源绑定对象的属性值
     */
    public void setSourceValue(T newValue) {
        PRINT_HELPER.enterPrint(this.toString() + ":setSourceValue.begin");
        {
            if (getType() == BindingType.TwoWay) {
                source.setProperty(sourcePropertyName,
                        converter.reverseConvert(newValue));
            }
        }
        PRINT_HELPER.exitPrint(this.toString() + ":setSourceValue.end");
    }

    @Override
    public String toString() {
        return "DataBinding:" + source.toString() + "->" + target.toString();
    }

}
