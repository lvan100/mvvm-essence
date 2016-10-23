package com.mvvm.view;

import com.mvvm.model.CollectionModel;
import com.mvvm.model.INotifyValueChanged;
import com.mvvm.model.Model;

import java.util.ArrayList;

import static com.print.PrintHelper.PRINT_HELPER;

/**
 * 列表视图控件
 */
public class ListView extends AbstractView {

    // 列表项集合
    public final CollectionModel<String> listValue = new CollectionModel<>(new ArrayList<>());

    {
        listValue.addNotifyValueChanged(new INotifyValueChanged() {

            @Override
            public void onValueChanged(Model model) {
                PRINT_HELPER.enterPrint(getId() + ":onValueChanged");
                {
                    show();
                }
                PRINT_HELPER.exit();
            }

        });
    }

    public ListView(String id) {
        setId(id);
    }

    @Override
    public void show() {
        PRINT_HELPER.enterPrint(getId() + ":show.begin");
        {
            PRINT_HELPER.enterPrint(getId() + ":show.listValue=");
            {
                PRINT_HELPER.enter();
                listValue.getValue().forEach(str -> {
                    PRINT_HELPER.print(str);
                });
                PRINT_HELPER.exit();
            }
            PRINT_HELPER.exit();
        }
        PRINT_HELPER.exitPrint(getId() + ":show.end");
    }

}
