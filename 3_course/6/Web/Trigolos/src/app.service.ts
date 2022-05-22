import { Injectable } from '@nestjs/common';

const st_style = [
  'nav ul {\n' +
    '    list-style: none;\n' +
    '}\n' +
    'li {\n' +
    '    margin: 0 5px;\n' +
    '}\n' +
    'ul {\n' +
    '    display: flex;\n' +
    '    justify-content: center;\n' +
    '    padding: 0;\n' +
    '    margin: 0;\n' +
    '}\n' +
    'nav a:hover {\n' +
    '    background: wheat;\n' +
    '}\n' +
    'a {\n' +
    '    display: block;\n' +
    '    text-decoration: none;\n' +
    '    color: black;\n' +
    '}\n' +
    '.active {\n' +
    '    background-color: magenta;\n' +
    '}\n' +
    '.text_shadow {\n' +
    '    text-shadow: 1px 1px 4px gray;\n' +
    '}\n' +
    '.bold {\n' +
    '    text-transform: uppercase;\n' +
    '}',
];

let user = '';
let haveCustomer = false;

@Injectable()
export class AppService {
  root() {
    return {
      title: 'Триголос Алексей M33041. Guten Tag, meine Damen und Herren :D!',
      style: st_style,
      nav: [
        { href: '#work_experience', name: 'Опыт работы', active: '!' },
        { href: '#skills', name: 'Навыки', active: '' },
        { href: '#contacts', name: 'Контакты', active: '' },
        {
          href: '/',
          name: 'Главная страница',
          active: 'active',
          main_nav: [
            { href: '/second', name: 'Вторая страница' },
            { href: '/third', name: 'Третья страница' },
            { href: '/fourth', name: '5 лаба' },
            { href: '/tasks', name: 'Хаски' },
          ],
        },
      ],
      have_customer: haveCustomer,
      customer: user,
      footer: '© 2021 Триголос Алексей',
      time: '',
    };
  }

  second() {
    return {
      title: 'Простая страничка html',
      style: st_style,
      nav: [
        { href: '/', name: 'Стартовая' },
        { href: '/second', name: 'Вторая страница' },
        { href: '/third', name: 'Третья страница' },
        { href: '/fourth', name: '5 лаба' },
        { href: '/tasks', name: 'Хаски' },
      ],
      main_content_page: 'Вторая страница',
      have_customer: haveCustomer,
      customer: user,
      footer: '© 2021 Триголос Алексей',
      time: '',
    };
  }

  third() {
    return {
      title: 'Простая страничка html',
      style: st_style,
      nav: [
        { href: '/', name: 'Стартовая' },
        { href: '/second', name: 'Вторая страница' },
        { href: '/third', name: 'Третья страница' },
        { href: '/fourth', name: '5 лаба' },
        { href: '/tasks', name: 'Хаски' },
      ],
      main_content_page: 'Третья страница',
      have_customer: haveCustomer,
      customer: user,
      footer: '© 2021 Триголос Алексей',
      time: '',
    };
  }

  fourth() {
    return {
      title: 'Простая страничка html',
      style: st_style,
      nav: [
        { href: '/', name: 'Стартовая' },
        { href: '/second', name: 'Вторая страница' },
        { href: '/third', name: 'Третья страница' },
        { href: '/fourth', name: '5 лаба' },
        { href: '/tasks', name: 'Хаски' },
      ],
      have_customer: haveCustomer,
      customer: user,
      footer: '© 2021 Триголос Алексей',
      time: '',
    };
  }

  tasks() {
    return {
      title: 'Простая страничка html',
      style: st_style,
      nav: [
        { href: '/', name: 'Стартовая' },
        { href: '/second', name: 'Вторая страница' },
        { href: '/third', name: 'Третья страница' },
        { href: '/fourth', name: '5 лаба' },
        { href: '/tasks', name: 'Хаски' },
      ],
      have_customer: haveCustomer,
      customer: user,
      footer: '© 2021 Триголос Алексей',
      time: '',
    };
  }

  changeCustomer(json, response) {
    if (json.name == '') {
      response.clearCookie('LogCookieTAPLocalHost');
      haveCustomer = false;
    } else {
      haveCustomer = true;
      response.clearCookie('LogCookieTAPLocalHost');
      response.cookie('LogCookieTAPLocalHost', json.name);
      user = json.name;
    }
    return this.second();
  }
}
