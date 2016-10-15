package com.example;

import com.example.viewmodel.StudentViewModel;

public class Main {

    public static void main(String[] args) {

        StudentViewModel studentViewModel = new StudentViewModel();
        studentViewModel.show();

        System.out.println();
        System.out.println("change student name:");
        studentViewModel.student.setName("XiaoMing");

        System.out.println();
        studentViewModel.show();

        System.out.println();
        System.out.println("change student score:");
        studentViewModel.student.setScore(85);

        System.out.println();
        studentViewModel.show();
    }

}
