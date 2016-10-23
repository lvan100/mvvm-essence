package com.exampl2.viewmodel;

import com.mvvm.binding.BindingType;
import com.mvvm.binding.DataBinding;
import com.mvvm.model.CollectionModel;
import com.mvvm.view.ListView;

import java.util.ArrayList;
import java.util.Collection;

/**
 * 视图和领域模型。
 */
public class ListViewModel {

    public final ListView listView = new ListView("list_view");

    public final CollectionModel<String> listModel = new CollectionModel<>(new ArrayList<>());

    public ListViewModel() {

        listModel.add("LiLei");
        System.out.println();

        listModel.add("XiaoMing");
        System.out.println();

        listView.listValue.setDataBinding(new DataBinding<Collection<String>>(
                BindingType.OneWay, listModel));
        System.out.println();

        listModel.remove("XiaoMing");
        System.out.println();

        listModel.add("HanMeiMei");
        System.out.println();

        listModel.clear();
        System.out.println();
    }

    public void show() {
        listView.show();
    }

}
