import { MiddlewareConsumer, Module, NestModule } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { UsersModule } from './users/users.module';
import { UsersController } from './users/users.controller';
import { UsersService } from './users/users.service';
import { MyPostsService } from './mypost/myposts.service';
import { MyPostsModule } from './mypost/myposts.module';
import { MyPostsController } from './mypost/myposts.controller';
import { AuthModule } from './auth/auth.module';
import { AuthMiddleware } from './auth/auth.middleware';
import { MessageModule } from './websocket/message.module';

@Module({
  imports: [
    UsersModule,
    MyPostsModule,
    MessageModule,
    AuthModule.forRoot({
      // These are the connection details of the app you created on supertokens.com
      connectionURI:
        'https://9baf5c31c54c11eca199e7bd956c96c9-us-east-1.aws.supertokens.io:3568',
      apiKey: 'YqBHwryoT=rYJOoOlpFmrFIE7pyoY0',
      appInfo: {
        // Learn more about this on https://supertokens.com/docs/emailpassword/appinfo
        appName: 'trigolos-web-app',
        apiDomain: 'http://localhost:12345',
        websiteDomain: 'http://localhost:3000',
        apiBasePath: '/auth',
        websiteBasePath: '/auth',
      },
    }),
  ],
  controllers: [AppController, UsersController, MyPostsController],
  providers: [AppService, UsersService, MyPostsService],
})
export class AppModule implements NestModule {
  configure(consumer: MiddlewareConsumer) {
    consumer.apply(AuthMiddleware).forRoutes(UsersController);
  }
}
