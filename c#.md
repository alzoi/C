
h1Сериализация
https://metanit.com/sharp/tutorial/6.4.php

```c#

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Serialization;

namespace WindowsFormsApp2 {
   public partial class Form1 : Form {
      public Form1() {
         InitializeComponent();
      }

      private void button1_Click(object sender, EventArgs e) {
         string filename = "C:\\Users\\us\\Downloads\\01.xml";
         
         // Список объектов.
         List<Person> LT_pers = new List<Person>();
         
         // Объекты для сериализации.
         Person person1 = new Person("Tom", 29);
         Person person2 = new Person("Bill", 25);
         // Добавляем объекты в список.
         LT_pers.Add(person1);
         LT_pers.Add(person2);

         // Сериализуем список для записи в XML файл.
         XmlSerializer xs = new XmlSerializer(typeof(List<Person>));
         // Запись
         Stream writer = new FileStream(filename, FileMode.Create);
         xs.Serialize(writer, LT_pers);
         writer.Close();
         
         List<Person> LT_pers2 = new List<Person>();
         // Чтение XML файла.
         Stream reader = new FileStream(filename, FileMode.Open);
         // Десериализация данных.
         LT_pers2 = (List<Person>)xs.Deserialize(reader);
         reader.Close();

         Console.WriteLine(LT_pers2[1].Age);
      }
   }
}

[Serializable]
// Класс для сериализации данных.
public class Person {
   public string Name { get; set; }
   public int Age { get; set; }

   // Конструктор без параметров.
   public Person() { }

   public Person(string name, int age) {
      Name = name;
      Age = age;
   }
}

