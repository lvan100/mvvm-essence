package com.example.model;

import com.mvvm.notify.IPropertyChangedSupport;
import com.mvvm.notify.PropertyChangedHandler;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 学生信息，领域模型
 */
public class Student implements IPropertyChangedSupport {

    // 学生姓名
    private String name;

    public static final String nameProperty = "name";

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
        handler.notifyPropertyChanged(null, this, nameProperty);
    }

    //学生分数
    private int score;

    public static final String scoreProperty = "score";

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
        handler.notifyPropertyChanged(null, this, scoreProperty);
    }

    @Override
    public Object getProperty(String propertyName) {
        PRINT_HELPER.print(this.toString() + ":getProperty[\"" + propertyName + "\"]");

        if (nameProperty.equals(propertyName)) {
            return name;
        }

        if (scoreProperty.equals(propertyName)) {
            return score;
        }

        return null;
    }

    @Override
    public void setProperty(String propertyName, Object value) {
        PRINT_HELPER.print(this.toString() + ":setProperty[\"" + propertyName + "\"]");

        if (nameProperty.equals(propertyName)) {
            name = (String) value;
        }

        if (scoreProperty.equals(propertyName)) {
            score = (Integer) value;
        }
    }

    /**
     * 属性变化处理器
     */
    private PropertyChangedHandler handler = new PropertyChangedHandler();

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return handler;
    }

    @Override
    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
        PRINT_HELPER.enterPrint(this.toString() + "Student:onPropertyChanged");

        setProperty(propertyName, eventSource.getProperty(propertyName));

        PRINT_HELPER.enterPrint(this.toString() + "notifyPropertyChanged.begin");
        handler.notifyPropertyChanged(eventSource, this, scoreProperty);
        PRINT_HELPER.exitPrint(this.toString() + "notifyPropertyChanged.end");

        PRINT_HELPER.exit();
    }

}
