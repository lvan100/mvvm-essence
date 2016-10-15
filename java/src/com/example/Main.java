package com.example;

import com.example.viewmodel.MyViewModel;

public class Main {

    public static void main(String[] args) {
        MyViewModel myViewModel = new MyViewModel();
        myViewModel.show();

        System.out.println();
        System.out.println();

        System.out.println("Main:changeModelDirectly");
        myViewModel.getMyModel1().setValue("2");

        System.out.println();
        System.out.println();

        myViewModel.show();

        System.out.println();

        System.out.println("myModel1=" +
                myViewModel.getMyModel1().getValue());

        System.out.println();
        System.out.println();

        myViewModel.getTextBox3().setText("3");

        System.out.println();
        System.out.println();

        myViewModel.show();

        System.out.println();

        System.out.println("myModel1=" +
                myViewModel.getMyModel1().getValue());

        System.out.println();
        System.out.println();

        myViewModel.getTextBox1().setText("4");

        System.out.println();
        System.out.println();

        myViewModel.show();

        System.out.println();

        System.out.println("myModel1=" +
                myViewModel.getMyModel1().getValue());
    }

}
