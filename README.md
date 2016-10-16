# mvvm-essence
通过使用Java语言实现的DEMO展示MVVM设计模式的精髓！

当前对于数据绑定的实现有两个版本：一个版本是类WPF模式，另一种是纯Model模式。WPF将绑定源称为Model，而将绑定目标称为DependencyObject，这在一定程度上掩盖了数据绑定背后实现的机制，实际上WPF中的Model和DependencyObject应该是同源的，所以基于此论断发展出了纯Model模式。在纯Model模式中，所有的Model都是可绑定的，这样就将WPF中的Model和DependencyObject合并成为一个概念——BindableModel，可绑定的Model。事实上在下面的示例比较中你会发现，第二种实现要比第一种简单太多。

## 纯Model模式

### Model

```
public class Student {

    // 学生姓名模型
    public final Model<String> nameValue = new Model<>("");

    //学生分数模型
    public final Model<Integer> scoreValue = new Model<>(0);

}
```

### View

```
public class TextBox extends AbstractView {

    /**
     * 输入框文本数据模型
     */
    public final Model<String> textValue = new Model<>("");

}
```


### ViewModel

```
public class StudentViewModel {

    // 学生信息
    public Student student = new Student();

    // 学生信息视图
    public StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        // 双向绑定学生分数
        // student.score -- binding --> studentView.textBoxStudentScore --> ...show

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
        // studentView.textBoxStudentScore --> student.score

        studentView.textBoxStudentScore.setText("75");
        System.out.println();
    }

}
```

## WPF模式

### Model

Model只需要实现IPropertyChangedSupport接口并在值更新时通知变化。

```
public class Student implements IPropertyChangedSupport {

    private String name;
    public static final String nameProperty = "name";

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
	handler.notifyPropertyChanged(null, this, nameProperty);
    }

    /**
     * 属性变化处理器
     */
    private PropertyChangedHandler handler = new PropertyChangedHandler();

    @Override
    public PropertyChangedHandler getPropertyChangedHandler() {
        return handler;
    }

}
```

### View 

View只需要创建DependencyObject并为其提供绑定。

```
public class TextBox extends AbstractView {

    public static final String textProperty = "textValue";
    private DependencyObject<String> textValue = new DependencyObject<>("");

    public DependencyObject<String> getText() {
        return textValue;
    }

    public void setText(String value) {
        textValue.setValue(value);
    }

    /**
     * 为属性设置数据绑定。
     */
    public void setDataBinding(String propertyName, DataBinding<?> binding) {

        if (textProperty.equals(propertyName)) {
            ((DataBinding<String>) binding).setTarget(textValue);
        }

        // 完成数据绑定组装
        binding.build();
    }

}
```

### ViewModel

ViewModel只需要连接数据模型和View的DependencyObject对象即可。

```
public class StudentViewModel {

    // 学生信息
    public Student student = new Student();

    // 学生信息视图
    public StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        // 双向绑定学生分数
        // student.score -- binding --> studentView.textBoxStudentScore --> ...show

        DataBinding<String> binding = new DataBinding<>(
                BindingType.TwoWay, student, Student.scoreProperty);

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

        studentView.textBoxStudentScore.setDataBinding(
                TextBox.textProperty, binding);

        // 双向绑定修改学生分数
        // student.score --> studentView.textBoxStudentScore --> ...show

        student.setScore(45);
        System.out.println();

        // 双向绑定修改学生分数
        // studentView.textBoxStudentScore --> student.score

        studentView.textBoxStudentScore.setText("75");
        System.out.println();
    }

}
```
