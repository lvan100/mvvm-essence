package com.example.view;

import com.mvvm.binding.BindingType;
import com.mvvm.binding.DataBinding;
import com.mvvm.model.Model;
import com.mvvm.notify.OnValueChanged;
import com.mvvm.view.AbstractView;
import com.mvvm.view.Command;

/**
 * 文本输入框控件。
 */
public class TextBox extends AbstractView {

    public static final String textProperty = "textValue";

    /**
     * 文本数据模型
     */
    private Model<String> textValue = new Model<String>("");

    {
        // 文本内容的更新应该肯定会引起控件界面的刷新 //
        textValue.addValueChanged(new OnValueChanged<String>() {

            @Override
            public void onValueChanged(String newValue) {

                if (textValueChanged != null) {
                    textValueChanged.onCommand(TextBox.this);
                }

                show();
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

        try {
            textValue.setValue(value);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    /**
     * 为属性设置数据绑定。
     */
    public void setDataBinding(String propertyName, DataBinding<?> binding) {

        if (textProperty.equals(propertyName)) {

            DataBinding<String> bd = (DataBinding<String>) binding;
            bd.setTarget(textValue);

            binding.getSource().addValueChanged(new OnValueChanged<String>() {

                @Override
                public void onValueChanged(String newValue) {
                    bd.setTargetValue(newValue);
                }

            });

            if (binding.getType() == BindingType.TwoWay) {

                textValue.addValueChanged(new OnValueChanged<String>() {

                    @Override
                    public void onValueChanged(String newValue) {
                        try {
                            bd.setSourceValue(newValue);
                        } catch (IllegalAccessException e) {
                            e.printStackTrace();
                        }
                    }

                });
            }

            // 刷新源数据 //
            binding.getSource().refresh();
        }
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
        System.out.println(getId() + ":show");
        System.out.println(getId() + ":textValue=" + getText().getValue());
    }

}
