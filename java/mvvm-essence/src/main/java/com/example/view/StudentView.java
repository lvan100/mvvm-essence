package com.example.view;

import com.mvvm.view.AbstractView;
import com.mvvm.view.TextBox;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 学生信息视图
 */
public class StudentView extends AbstractView {

    // 学生姓名
    public TextBox textBoxStudentName = new TextBox("textBoxStudentName");

    // 学生分数
    public TextBox textBoxStudentScore = new TextBox("textBoxStudentScore");

    // 学生评级
    public TextBox textBoxStudentLevel = new TextBox("textBoxStudentLevel");

    public StudentView(String id) {
        setId(id);
    }

    @Override
    public void show() {
        PRINT_HELPER.enterPrint(getId() + ":show.begin");

        textBoxStudentName.show();
        textBoxStudentScore.show();
        textBoxStudentLevel.show();

        PRINT_HELPER.exitPrint(getId() + ":show.end");
    }

}
