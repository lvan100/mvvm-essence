package com.example.model;

import com.mvvm.notify.IPropertyChangedSupport;
import com.mvvm.notify.PropertyChangedHandler;

import java.util.Objects;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 学生信息，数据模型
 */
public class Student implements IPropertyChangedSupport {

    // 学生姓名
    private String name;

    public static final String nameProperty = "name";

    public String getName() {
        return name;
    }

    public void setName(String name) {
        PRINT_HELPER.enterPrint(this.toString() + ":setName.begin");
        {
            if (Objects.deepEquals(this.name, name)) {
                PRINT_HELPER.exitPrint(this.toString() + ":setName.end");

            } else {
                PRINT_HELPER.print(this.toString() + ":setName="
                        + this.name + "->" + name);

                this.name = name;
                PRINT_HELPER.exitPrint(this.toString() + ":setName.end");

                PRINT_HELPER.enterPrint(this.toString() + ":notifyPropertyChanged.begin");
                {
                    handler.notifyPropertyChanged(this, nameProperty);
                }
                PRINT_HELPER.exitPrint(this.toString() + ":notifyPropertyChanged.end");
            }
        }
    }

    //学生分数
    private int score;

    public static final String scoreProperty = "score";

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        PRINT_HELPER.enterPrint(this.toString() + ":setScore.begin");
        {
            if (Objects.deepEquals(this.score, score)) {
                PRINT_HELPER.exitPrint(this.toString() + ":setScore.end");

            } else {
                PRINT_HELPER.print(this.toString() + ":setScore="
                        + this.score + "->" + score);

                this.score = score;
                PRINT_HELPER.exitPrint(this.toString() + ":setScore.end");

                PRINT_HELPER.enterPrint(this.toString() + ":notifyPropertyChanged.begin");
                {
                    handler.notifyPropertyChanged(this, scoreProperty);
                }
                PRINT_HELPER.exitPrint(this.toString() + ":notifyPropertyChanged.end");
            }
        }
    }

    @Override
    public Object getProperty(String propertyName) {
        PRINT_HELPER.print(this.toString() + ":getProperty[\"" + propertyName + "\"]");

        if (nameProperty.equals(propertyName)) {
            return getName();
        }

        if (scoreProperty.equals(propertyName)) {
            return getScore();
        }

        return null;
    }

    @Override
    public void setProperty(String propertyName, Object value) {
        PRINT_HELPER.print(this.toString() + ":setProperty[\"" + propertyName + "\"]");

        if (nameProperty.equals(propertyName)) {
            setName((String) value);
        }

        if (scoreProperty.equals(propertyName)) {
            setScore((Integer) value);
        }
    }

    /**
     * 属性变化处理器
     */
    private final PropertyChangedHandler handler = new PropertyChangedHandler();

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return handler;
    }

}
