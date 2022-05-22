import {
  Controller,
  Get,
  Post,
  Render,
  Body,
  UseInterceptors,
  Res,
} from '@nestjs/common';
import { AppService } from './app.service';
import { Response } from 'express';
import { NewUser } from './dto/app.dto';

import {
  ApiBody,
  ApiOperation,
  ApiRequestTimeoutResponse,
  ApiTags,
} from '@nestjs/swagger';
import { TimeInterceptor } from './time.interceptor';

@ApiTags('app')
@Controller()
@UseInterceptors(new TimeInterceptor())
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  @Render('index')
  @ApiOperation({ summary: 'Main page' })
  root() {
    return this.appService.root();
  }

  @Get('second')
  @Render('second')
  @ApiOperation({ summary: 'Register page' })
  @ApiRequestTimeoutResponse()
  second() {
    return this.appService.second();
  }

  @Get('third')
  @Render('third')
  @ApiOperation({ summary: 'Just page' })
  third() {
    return this.appService.third();
  }

  @Get('fourth')
  @Render('fourth')
  @ApiOperation({ summary: 'Lessons page' })
  fourth() {
    return this.appService.fourth();
  }

  @Get('tasks')
  @Render('tasks')
  @ApiOperation({ summary: 'Tasks page' })
  tasks() {
    return this.appService.tasks();
  }

  @Post('second')
  @ApiOperation({ summary: 'Change user' })
  @ApiBody({ type: NewUser })
  async setProfile(
    @Body() newUser: NewUser,
    @Res({ passthrough: true }) response: Response,
  ) {
    return this.appService.changeCustomer(newUser, response);
  }
}
