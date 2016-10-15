package com.example.viewmodel;

import com.example.model.Student;
import com.example.view.StudentView;
import com.mvvm.binding.BindingType;
import com.mvvm.binding.DataBinding;
import com.mvvm.binding.ValueConverter;
import com.mvvm.model.Model;
import com.mvvm.view.TextBox;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 视图和领域模型。
 */
public class StudentViewModel {

    // 学生信息
    public Student student = new Student();

    // 学生信息视图
    public StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        PRINT_HELPER.enterPrint("studentView.textBoxStudentName.setDataBinding.begin");

        studentView.textBoxStudentName.setDataBinding(
                TextBox.textProperty, new DataBinding<String>(
                        BindingType.TwoWay, student, Student.nameProperty));

        PRINT_HELPER.exitPrint("studentView.textBoxStudentName.setDataBinding.end");
        System.out.println();

        PRINT_HELPER.enterPrint("studentView.textBoxStudentScore.setDataBinding.begin");

        DataBinding<String> binding = new DataBinding<String>(
                BindingType.TwoWay, student, Student.scoreProperty);

        binding.setValueConverter(new ValueConverter<String>() {
            @Override
            public String convert(Object value) {
                return value.toString();
            }
        });

        studentView.textBoxStudentScore.setDataBinding(
                TextBox.textProperty, binding);

        PRINT_HELPER.exitPrint("studentView.textBoxStudentScore.setDataBinding.end");
        System.out.println();

        PRINT_HELPER.enterPrint("studentView.textBoxStudentLevel.setDataBinding.begin");

        binding = new DataBinding<String>(
                BindingType.OneWay, studentView.textBoxStudentScore.getText()
                , Model.valueProperty);

        binding.setValueConverter(new ValueConverter<String>() {
            @Override
            public String convert(Object value) {
                int score = Integer.valueOf((String) value);
                if (score < 60) {
                    return "不及格";
                } else if (score < 70) {
                    return "一般";
                } else
                    return "优秀";
            }
        });

        studentView.textBoxStudentLevel.setDataBinding(
                TextBox.textProperty, binding);

        PRINT_HELPER.exitPrint("studentView.textBoxStudentLevel.setDataBinding.end");
        System.out.println();
    }

    public void show() {
        studentView.show();
    }

}
