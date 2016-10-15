package com.example.viewmodel;

import com.example.view.TextBox;
import com.mvvm.binding.BindingType;
import com.mvvm.binding.DataBinding;
import com.mvvm.model.Model;

/**
 * 视图和领域模型。
 */
public class MyViewModel {

    private TextBox myTextBox0 = new TextBox("myTextBox0");
    private TextBox myTextBox1 = new TextBox("myTextBox1");
    private TextBox myTextBox2 = new TextBox("myTextBox2");
    private TextBox myTextBox3 = new TextBox("myTextBox3");

    {
        myTextBox0.setText(myTextBox0.getId());
        System.out.println();

        myTextBox1.setText(myTextBox1.getId());
        System.out.println();

        myTextBox2.setText(myTextBox2.getId());
        System.out.println();

        myTextBox3.setText(myTextBox3.getId());
        System.out.println();
    }

    public TextBox getTextBox1() {
        return myTextBox1;
    }

    public TextBox getTextBox3() {
        return myTextBox3;
    }

    private Model<String> myModel0 = new Model<>(true, "0");
    private Model<String> myModel1 = new Model<>("1");

    public Model<String> getMyModel1() {
        return myModel1;
    }

    public MyViewModel() {

        myTextBox2.setDataBinding(TextBox.textProperty,
                new DataBinding(BindingType.OneWay, myModel0, myModel0.valueProperty));

        System.out.println();

        myTextBox3.setDataBinding(TextBox.textProperty,
                new DataBinding(BindingType.TwoWay, myModel1, myModel1.valueProperty));

        System.out.println();

        myTextBox1.setDataBinding(TextBox.textProperty,
                new DataBinding(BindingType.TwoWay, myTextBox3.getText(), myModel1.valueProperty));

        System.out.println();

        myTextBox3.setTextChangedCommand(source ->
                System.out.println("MyViewModel.myTextBox3:onCommand"));

        myTextBox1.setTextChangedCommand(source ->
                System.out.println("MyViewModel.myTextBox1:onCommand"));
    }

    public void show() {

        myTextBox0.show();
        System.out.println();

        myTextBox1.show();
        System.out.println();

        myTextBox2.show();
        System.out.println();

        myTextBox3.show();
    }

}
