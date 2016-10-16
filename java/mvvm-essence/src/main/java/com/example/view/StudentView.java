package com.example.view;

import com.mvvm.model.BindableModel;
import com.mvvm.model.EmptyModel;
import com.mvvm.model.Model;
import com.mvvm.view.AbstractView;
import com.mvvm.view.TextBox;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 学生信息视图
 */
public class StudentView extends AbstractView {

    /**
     * 视图标题数据模型
     */
    public final Model<String> titleValue = new Model<>("myView");

    {
        // 更新标题会引起界面的刷新
        titleValue.bindModel(new EmptyModel() {

            @Override
            public void onValueChanged(BindableModel eventSource) {
                PRINT_HELPER.enterPrint(getId() + ":onValueChanged");
                {
                    show();
                }
                PRINT_HELPER.exit();
            }

        });
    }

    // 学生姓名控件
    public final TextBox textBoxStudentName = new TextBox("textBoxStudentName");

    // 学生分数控件
    public final TextBox textBoxStudentScore = new TextBox("textBoxStudentScore");

    // 学生评级控件
    public final TextBox textBoxStudentLevel = new TextBox("textBoxStudentLevel");

    public StudentView(String id) {
        setId(id);
    }

    public String getTitle() {
        return titleValue.getValue();
    }

    public void setTitle(String value) {
        PRINT_HELPER.enterPrint(getId() + ":setTitle.begin");
        {
            titleValue.setValue(value);
        }
        PRINT_HELPER.exitPrint(getId() + ":setTitle.end");
    }

    @Override
    public void show() {
        PRINT_HELPER.enterPrint(getId() + ":show.begin");

        PRINT_HELPER.enterPrint(getId() + ":title.show.begin");
        {
            PRINT_HELPER.enter();
            PRINT_HELPER.print(getId() + ":title=" + titleValue.getValue());
            PRINT_HELPER.exit();
        }
        PRINT_HELPER.exitPrint(getId() + ":title.show.end");

        textBoxStudentName.show();
        textBoxStudentScore.show();
        textBoxStudentLevel.show();

        PRINT_HELPER.exitPrint(getId() + ":show.end");
    }

}
