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

        // 更新未绑定的学生信息视图标题
        // studentView.titleValue --> ...show

        studentView.setTitle("Student");
        System.out.println();

        // 未绑定前修改学生姓名
        // student.name --> ...

        student.setName("Lily");
        System.out.println();

        // 单向绑定学生姓名
        // student.name -- binding --> studentView.textBoxStudentName --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentName.setDataBinding.begin");

        studentView.textBoxStudentName.setDataBinding(
                TextBox.textProperty, new DataBinding<String>(
                        BindingType.OneWay, student, Student.nameProperty));

        PRINT_HELPER.exitPrint("studentView.textBoxStudentName.setDataBinding.end");
        System.out.println();

        // 单向绑定学生名称后修改学生姓名
        // student.name --> studentView.textBoxStudentName --> ...show

        student.setName("Jim");
        System.out.println();

        // 单向绑定学生名称后修改学生姓名
        // studentView.textBoxStudentName --> ...

        studentView.textBoxStudentName.setText("Green");
        System.out.println();

        // 双向绑定学生分数
        // student.score -- binding --> studentView.textBoxStudentScore --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentScore.setDataBinding.begin");

        DataBinding<String> binding = new DataBinding<>(
                BindingType.TwoWay, student, Student.scoreProperty);

        binding.setValueConverter(new ValueConverter<String>() {

            @Override
            public String convert(Object value) {
                return value.toString();
            }

            @Override
            public Object reverseConvert(String value) {
                return Integer.valueOf(value);
            }

        });

        studentView.textBoxStudentScore.setDataBinding(
                TextBox.textProperty, binding);

        PRINT_HELPER.exitPrint("studentView.textBoxStudentScore.setDataBinding.end");
        System.out.println();

        // 双向绑定修改学生分数
        // student.score --> studentView.textBoxStudentScore --> ...show

        student.setScore(45);
        System.out.println();

        // 双向绑定修改学生分数
        // studentView.textBoxStudentScore --> student.score

        studentView.textBoxStudentScore.setText("75");
        System.out.println();

        // 单向绑定学生成绩水平
        // studentView.textBoxStudentScore -- binding --> studentView.textBoxStudentLevel --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentLevel.setDataBinding.begin");

        binding = new DataBinding<>(
                BindingType.OneWay, studentView.textBoxStudentScore.getText()
                , Model.valueProperty);

        binding.setValueConverter(new ValueConverter<String>() {

            @Override
            public String convert(Object value) {
                int score = Integer.valueOf((String) value);
                if (score < 60) {
                    return "不及格";
                } else if (score < 80) {
                    return "一般";
                } else
                    return "优秀";
            }

        });

        studentView.textBoxStudentLevel.setDataBinding(
                TextBox.textProperty, binding);

        PRINT_HELPER.exitPrint("studentView.textBoxStudentLevel.setDataBinding.end");
        System.out.println();

        // 学生分数和成绩水平单向绑定后修改学生分数
        // student.score --> studentView.textBoxStudentScore --> studentView.textBoxStudentLevel -->...show

        student.setScore(90);
        System.out.println();

        // 学生分数和成绩水平单向绑定后修改学生分数
        // student.score --> studentView.textBoxStudentScore --> studentView.textBoxStudentLevel -->...show

        studentView.textBoxStudentScore.setText("10");
        System.out.println();
    }

    public void show() {
        studentView.show();
    }

}
