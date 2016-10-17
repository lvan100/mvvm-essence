package com.mvvm.view;

import com.mvvm.model.INotifyValueChanged;
import com.mvvm.model.Model;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 文本输入框控件。
 */
public class TextBox extends AbstractView {

    /**
     * 输入框文本数据模型
     */
    public final Model<String> textValue = new Model<>("");

    {
        // 更新文本内容会引起界面的刷新
        textValue.addNotifyValueChanged(new INotifyValueChanged() {

            @Override
            public void onValueChanged(Model model) {
                PRINT_HELPER.enterPrint(getId() + ":onValueChanged");

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

    public String getText() {
        return textValue.getValue();
    }

    public void setText(String value) {
        PRINT_HELPER.enterPrint(getId() + ":setText.begin");
        {
            textValue.setValue(value);
        }
        PRINT_HELPER.exitPrint(getId() + ":setText.end");
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
