# Generated by Django 3.1.1 on 2020-09-12 02:14

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('mysiteapp', '0002_auto_20200912_0209'),
    ]

    operations = [
        migrations.CreateModel(
            name='Choice',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('choice_text', models.CharField(max_length=200)),
                ('votes', models.IntegerField(default=0)),
            ],
        ),
        migrations.CreateModel(
            name='Question',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('question_text', models.CharField(max_length=200)),
                ('pub_date', models.DateTimeField(verbose_name='date published')),
            ],
        ),
        migrations.RemoveField(
            model_name='commentmodel',
            name='movie',
        ),
        migrations.RemoveField(
            model_name='moviemodel',
            name='actors',
        ),
        migrations.DeleteModel(
            name='ActorModel',
        ),
        migrations.DeleteModel(
            name='CommentModel',
        ),
        migrations.DeleteModel(
            name='MovieModel',
        ),
        migrations.AddField(
            model_name='choice',
            name='question',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='mysiteapp.question'),
        ),
    ]