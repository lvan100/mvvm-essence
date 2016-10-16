package com.example.model;

import com.mvvm.model.Model;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 学生信息，领域模型
 */
public class Student {

    // 学生姓名模型
    public final Model<String> nameValue = new Model<>("");

    //学生分数模型
    public final Model<Integer> scoreValue = new Model<>(0);

    public String getName() {
        return nameValue.getValue();
    }

    public void setName(String name) {
        PRINT_HELPER.enterPrint(this.toString() + ":setName.begin");
        {
            nameValue.setValue(name);
        }
        PRINT_HELPER.exitPrint(this.toString() + ":setName.end");
    }

    public int getScore() {
        return scoreValue.getValue();
    }

    public void setScore(int score) {
        PRINT_HELPER.enterPrint(this.toString() + ":setScore.begin");
        {
            scoreValue.setValue(score);
        }
        PRINT_HELPER.exitPrint(this.toString() + ":setScore.end");
    }

}
