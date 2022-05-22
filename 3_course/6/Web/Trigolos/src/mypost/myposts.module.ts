import { Module } from '@nestjs/common';
import { MyPostsController } from './myposts.controller';
import { MyPostsService } from './myposts.service';

@Module({
  controllers: [MyPostsController],
  providers: [MyPostsService],
  exports: [MyPostsService],
})
export class MyPostsModule {}
