package com.example.viewmodel;

import com.example.model.Student;
import com.example.view.StudentView;
import com.mvvm.binding.BindingType;
import com.mvvm.binding.DataBinding;
import com.mvvm.binding.ValueConverter;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 视图和领域模型。
 */
public class StudentViewModel {

    // 学生信息
    public final Student student = new Student();

    // 学生信息视图
    public final StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        // 更新未绑定的学生信息视图标题
        // studentView.titleValue --> ...show

        studentView.setTitle("Student");
        System.out.println();

        // 赋相同的值不会引发任何变化

        studentView.setTitle("Student");
        System.out.println();

        // 未绑定前修改学生姓名
        // student.name --> ...

        student.setName("Lily");
        System.out.println();

        // 单向绑定学生姓名
        // student.name --> studentView.textBoxStudentName --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentName.setDataBinding.begin");

        studentView.textBoxStudentName.textValue.setDataBinding(
                new DataBinding<>(BindingType.OneWay, student.nameValue));

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
        // student.score --> studentView.textBoxStudentScore --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentScore.setDataBinding.begin");

        DataBinding<String> binding = new DataBinding<>(
                BindingType.TwoWay, student.scoreValue);

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

        studentView.textBoxStudentScore.textValue.setDataBinding(binding);

        PRINT_HELPER.exitPrint("studentView.textBoxStudentScore.setDataBinding.end");
        System.out.println();

        // 双向绑定修改学生分数
        // student.score --> studentView.textBoxStudentScore --> ...show

        student.setScore(45);
        System.out.println();

        // 双向绑定修改学生分数
        // studentView.textBoxStudentScore --> student.score --> studentView.textBoxStudentScore --> ...show

        studentView.textBoxStudentScore.setText("75");
        System.out.println();

        // 单向绑定学生成绩水平
        // studentView.textBoxStudentScore --> studentView.textBoxStudentLevel --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentLevel.setDataBinding.begin");

        binding = new DataBinding<>(BindingType.OneWay,
                studentView.textBoxStudentScore.textValue);

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

        studentView.textBoxStudentLevel.textValue.setDataBinding(binding);

        PRINT_HELPER.exitPrint("studentView.textBoxStudentLevel.setDataBinding.end");
        System.out.println();

        // 学生分数和成绩水平单向绑定后修改学生分数
        // student.score --> studentView.textBoxStudentScore --> studentView.textBoxStudentLevel -->...show

        student.setScore(90);
        System.out.println();

        // 学生分数和成绩水平单向绑定后修改学生分数
        // studentView.textBoxStudentScore --> student.score --> studentView.textBoxStudentScore -->
        // studentView.textBoxStudentLevel -->...show

        studentView.textBoxStudentScore.setText("10");
        System.out.println();

        // 双向绑定学生分数控件和其备份控件
        // studentView.textBoxStudentScore --> studentView.textBoxStudentLevel -->
        // studentView.textBoxStudentScoreCopy --> ...show

        PRINT_HELPER.enterPrint("studentView.textBoxStudentScoreCopy.setDataBinding.begin");

        studentView.textBoxStudentScoreCopy.textValue.setDataBinding(new DataBinding<>(
                BindingType.TwoWay, studentView.textBoxStudentScore.textValue));

        PRINT_HELPER.exitPrint("studentView.textBoxStudentScoreCopy.setDataBinding.end");
        System.out.println();

        // 学生分数控件和其备份控件双向绑定后修改学生分数
        // student.score --> studentView.textBoxStudentScore --> studentView.textBoxStudentLevel -->
        // studentView.textBoxStudentScoreCopy --> ...show

        student.setScore(90);
        System.out.println();

        // 学生分数控件和其备份控件双向绑定后修改学生分数备份
        // studentView.textBoxStudentScoreCopy --> studentView.textBoxStudentScore --> student.score -->
        // studentView.textBoxStudentScore --> studentView.textBoxStudentLevel -->
        // studentView.textBoxStudentScoreCopy --> ...show

        studentView.textBoxStudentScoreCopy.setText("10");
        System.out.println();

        // 赋相同的值不会引发任何变化

        student.setScore(10);
        System.out.println();

        // 赋相同的值不会引发任何变化

        studentView.textBoxStudentScore.setText("10");
        System.out.println();

        // 赋相同的值不会引发任何变化

        studentView.textBoxStudentScoreCopy.setText("10");
        System.out.println();
    }

    public void show() {
        studentView.show();
    }

}
