package com.mvvm.binding;

import com.mvvm.notify.IPropertyChangedSupport;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 数据绑定的实现。
 *
 * @param <T>
 */
public class DataBinding<T> implements DataBindingInterface<T> {

    /**
     * 源绑定对象及其绑定属性
     */
    private String sourcePropertyName;
    private IPropertyChangedSupport source;

    /**
     * 目标绑定对象
     */
    private DependencyObject<T> target;

    /**
     * 绑定类型
     */
    private BindingType type;

    public DataBinding(BindingType type) {
        this.type = type;
    }

    public DataBinding(BindingType type, IPropertyChangedSupport source, String sourcePropertyName) {
        this.sourcePropertyName = sourcePropertyName;
        this.source = source;
        this.type = type;
    }

    @Override
    public BindingType getType() {
        return type;
    }

    @Override
    public void setType(BindingType type) {
        this.type = type;
    }

    @Override
    public IPropertyChangedSupport getSource() {
        return source;
    }

    @Override
    public void setSource(IPropertyChangedSupport source) {
        this.source = source;
    }

    @Override
    public String getSourcePropertyName() {
        return sourcePropertyName;
    }

    @Override
    public void setSourcePropertyName(String propertyName) {
        this.sourcePropertyName = propertyName;
    }

    @Override
    public DependencyObject<T> getTarget() {
        return target;
    }

    @Override
    public void setTarget(DependencyObject<T> target) {
        this.target = target;
    }

    /**
     * 值转换器
     */
    private ValueConverter<T> converter = new ValueConverter<T>() {
        @Override
        public T convert(Object value) {
            return (T) value;
        }
    };

    @Override
    public void setValueConverter(ValueConverter<T> converter) {
        this.converter = converter;
    }

    /**
     * 获取目标绑定对象的值
     */
    T getTargetValue() {
        System.out.println(this.toString() + ":getTargetValue");
        return target.getValue();
    }

    /**
     * 获取源绑定对象的属性值
     */
    T getSourceValue() {
        PRINT_HELPER.print(this.toString() + ":getSourceValue");
        return converter.convert(source.getProperty(sourcePropertyName));
    }

    /**
     * 设置源绑定对象的属性值
     */
    void setSourceValue(T newValue) {
        System.out.println(this.toString() + ":setSourceValue");
        source.setProperty(sourcePropertyName, newValue);
    }

    /**
     * 完成数据绑定的组装
     */
    public void build() {

        target.setDataBinding(this);

        source.getPropertyChangedHandler()
                .addPropertyChangedNotify(sourcePropertyName, target);

        if (getType() == BindingType.TwoWay) {
            target.getPropertyChangedHandler()
                    .addPropertyChangedNotify(target.valueProperty, source);
        }

        PRINT_HELPER.enterPrint(this.toString() + ":build.begin");

        if (source instanceof DependencyObject) {
            DependencyObject dependencyObj = (DependencyObject) source;
            dependencyObj.getPropertyChangedHandler().notifyPropertyChanged(
                    dependencyObj.getDataBinding().getSource(), source, sourcePropertyName);

        } else {
            source.getPropertyChangedHandler()
                    .notifyPropertyChanged(null, source, sourcePropertyName);
        }

        PRINT_HELPER.exitPrint(this.toString() + ":build.end");
    }

    @Override
    public String toString() {
        return "DataBinding:" + source.toString() + "->" + target.toString();
    }

}
