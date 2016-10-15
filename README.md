# mvvm-essence
通过使用Java语言实现的DEMO展示MVVM设计模式的精髓！

# Model

Model只需要实现IPropertyChangedSupport接口并在值更新时通知变化。

```
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

# View 

View只需要创建DependencyObject并为其提供绑定。

```
/**
 * 文本输入框控件。
 */
public class TextBox extends AbstractView {

    public static final String textProperty = "textValue";

    /**
     * 文本数据依赖对象
     */
    private DependencyObject<String> textValue = new DependencyObject<>("");

    {
        // 更新文本内容会引起界面的刷新
        textValue.getPropertyChangedHandler().addPropertyChangedNotify(
                DependencyObject.valueProperty, new EmptyPropertyChangedSupport() {

                    @Override
                    public void onPropertyChanged(IPropertyChangedSupport eventSource, String propertyName) {
                    }

                });
    }

    public TextBox(String id) {
        setId(id);
    }

    /**
     * 获取文本内容依赖对象
     */
    public DependencyObject<String> getText() {
        return textValue;
    }

    /**
     * 设置文本内容
     */
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

    /**
     * 文本内容发生变化的事件
     */
    private Command textValueChanged;

    /**
     * 设置文本内容发生变化的事件响应
     */
    public void setTextChangedCommand(Command command) {
        this.textValueChanged = command;
    }

}
```

# ViewModel

ViewModel只需要连接数据模型和View的DependencyObject对象即可。

```
/**
 * 视图和领域模型。
 */
public class StudentViewModel {

    // 学生信息
    public Student student = new Student();

    // 学生信息视图
    public StudentView studentView = new StudentView("studentView");

    public StudentViewModel() {

        // 单向绑定学生姓名
        // student.name -- binding --> studentView.textBoxStudentName --> ...show

        studentView.textBoxStudentName.setDataBinding(
                TextBox.textProperty, new DataBinding<String>(
                        BindingType.OneWay, student, Student.nameProperty));

        // 单向绑定学生名称后修改学生姓名
        // student.name --> studentView.textBoxStudentName --> ...show

        student.setName("Jim");
        System.out.println();

        // 单向绑定学生名称后修改学生姓名
        // studentView.textBoxStudentName --> ...

        studentView.textBoxStudentName.setText("Green");
        System.out.println();

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
