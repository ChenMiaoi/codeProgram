from flask import Flask, render_template

app = Flask(__name__)
# 如果需要自己指定render_template的搜索路径，就需要在构建的对象的时候使用template_folder关键字参数
# app = Flask(__name__, template_folder = r"path")

@app.route("/")
def index():
    context = {
        "username" : "芜湖"
    }
    return render_template("index.html", **context) # 注意Flask提供的模板渲染,文件路径必须在templates文件夹下，否则无法获取
    # 传入参数需要用字典，同时需要**获取关键字，在对应的html文件中，通过{{}}来使用

@app.route("/control")
def control():
    '''
        控制语句：
            语法：{%%}
            选择语句：
                {% if ... %} {% elif ... %} {% else %} {% endif %}
            循环语句：
                {% for ... in ... %} {% endfor %}
    '''
    context = {
        "age" : 18,
        "books" : ["红楼梦", "三国演义", "西游记", "水浒传"],
        "person" : {"name" : "Lily", "age" : "20"}
    }
    return render_template("control.html", **context);

if __name__ == "__main__":
    app.run(debug = True)