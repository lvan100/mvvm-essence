package com.example.view;

import com.mvvm.binding.DataBinding;
import com.mvvm.binding.DependencyObject;
import com.mvvm.notify.EmptyPropertyChangedSupport;
import com.mvvm.notify.IPropertyChangedSupport;
import com.mvvm.view.AbstractView;
import com.mvvm.view.TextBox;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 学生信息视图
 */
public class StudentView extends AbstractView {

    public static final String titleProperty = "titleValue";

    /**
     * 视图标题依赖对象
     */
    private DependencyObject<String> titleValue = new DependencyObject<>("myView");

    {
        // 更新标题会引起界面的刷新
        titleValue.getPropertyChangedHandler().addPropertyChangedNotify(
                DependencyObject.valueProperty, new EmptyPropertyChangedSupport() {

                    @Override
                    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
                        PRINT_HELPER.enterPrint(getId() + ":onPropertyChanged");

                        show();

                        PRINT_HELPER.exit();
                    }

                });
    }

    // 学生姓名
    public TextBox textBoxStudentName = new TextBox("textBoxStudentName");

    // 学生分数
    public TextBox textBoxStudentScore = new TextBox("textBoxStudentScore");

    // 学生评级
    public TextBox textBoxStudentLevel = new TextBox("textBoxStudentLevel");

    public StudentView(String id) {
        setId(id);
    }

    public DependencyObject<String> getTitle() {
        PRINT_HELPER.print(getId() + ":getTitle");
        return titleValue;
    }

    public void setTitle(String value) {
        PRINT_HELPER.enterPrint(getId() + ":setTitle.begin");
        titleValue.setValue(value);
        PRINT_HELPER.exitPrint(getId() + ":setTitle.end");
    }

    /**
     * 为属性设置数据绑定。
     */
    @Override
    public void setDataBinding(String propertyName, DataBinding<?> binding) {

        if (titleProperty.equals(propertyName)) {
            ((DataBinding<String>) binding).setTarget(titleValue);
        }

        // 完成数据绑定组装
        binding.build();
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
