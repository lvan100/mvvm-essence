package com.mvvm.view;

import com.mvvm.binding.DataBinding;
import com.mvvm.binding.DependencyObject;
import com.mvvm.model.Model;
import com.mvvm.notify.EmptyPropertyChangedSupport;
import com.mvvm.notify.IPropertyChangedSupport;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 文本输入框控件。
 */
public class TextBox extends AbstractView {

    public static final String textProperty = "textValue";

    /**
     * 文本数据模型
     */
    private DependencyObject<String> textValue = new DependencyObject<>("");

    {
        // 文本内容的更新应该肯定会引起控件界面的刷新 //
        textValue.getPropertyChangedHandler().addPropertyChangedNotify(
                textValue.valueProperty, new EmptyPropertyChangedSupport() {

                    @Override
                    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
                        PRINT_HELPER.enterPrint(getId() + ":onPropertyChanged");

                        if (textValueChanged != null) {
                            textValueChanged.onCommand(TextBox.this);
                        }

                        show();

                        PRINT_HELPER.exit();
                    }

                });
    }

    public TextBox(String id) {
        setId(id);
    }

    /**
     * 获取文本内容
     */
    public Model<String> getText() {
        System.out.println(getId() + ":getText");
        return textValue;
    }

    /**
     * 设置文本内容
     */
    public void setText(String value) {
        System.out.println(getId() + ":setText");
        textValue.setValue(value);
    }

    /**
     * 为属性设置数据绑定。
     */
    public void setDataBinding(String propertyName, DataBinding<?> binding) {

        if (textProperty.equals(propertyName)) {
            ((DataBinding<String>) binding).setTarget(textValue);
        }

        // 完成数据绑定组装
        binding.build();
    }

    /**
     * 文本内容发生变化的事件
     */
    private Command textValueChanged;

    /**
     * 设置文本内容发生变化的事件响应
     */
    public void setTextChangedCommand(Command command) {
        this.textValueChanged = command;
    }

    @Override
    public void show() {
        PRINT_HELPER.enterPrint(getId() + ":show.begin");

        PRINT_HELPER.enter();
        PRINT_HELPER.print(getId() + ":show[textValue=" + textValue.getValue() + "]");
        PRINT_HELPER.exit();

        PRINT_HELPER.exitPrint(getId() + ":show.end");
    }

}
