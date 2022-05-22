import { NestFactory } from '@nestjs/core';
import { NestExpressApplication } from '@nestjs/platform-express';
import supertokens from 'supertokens-node';
import { AppModule } from './app.module';
import { join, resolve } from 'path';
import hbs = require('hbs');
import * as cookieParser from 'cookie-parser';
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';
import { ValidationPipe } from '@nestjs/common';
import { HttpExceptionFilter } from './exceptions/http-exception.filter';
import { SupertokensExceptionFilter } from './auth/auth.filter';
import { middleware } from 'supertokens-node/framework/express';
import { errorHandler } from 'supertokens-node/framework/express';

async function bootstrap() {
  const app = await NestFactory.create<NestExpressApplication>(AppModule);
  app.enableCors({
    origin: ['http://localhost:3000'],
    allowedHeaders: ['content-type', ...supertokens.getAllCORSHeaders()],
    credentials: true,
  });
  app.use(middleware());
  app.useStaticAssets(resolve('./src/public'));
  app.setBaseViewsDir(resolve('./src/views'));
  app.setViewEngine('hbs');
  hbs.registerPartials(join(__dirname, '..', 'views', 'partials'));
  app.use(cookieParser());
  app.useGlobalPipes(new ValidationPipe());
  app.useGlobalFilters(
    new HttpExceptionFilter(),
    new SupertokensExceptionFilter(),
  );
  const config = new DocumentBuilder()
    .addCookieAuth('sAccessToken', {
      type: 'http',
      scheme: 'basic',
    })
    .setTitle('Example')
    .setDescription('The API description')
    .setVersion('1.0')
    .build();
  app.use(errorHandler());
  const document = SwaggerModule.createDocument(app, config);
  SwaggerModule.setup('api', app, document);
  const port = process.env.PORT || 3000;
  await app.listen(port);
}

bootstrap();
