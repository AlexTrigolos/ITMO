import {
  BadRequestException,
  Body,
  Controller,
  Delete,
  Get,
  HttpStatus,
  Post,
  Put,
  Query,
  UseGuards,
} from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';
import { User } from './entity/user.entity';

import {
  ApiBody,
  ApiCookieAuth,
  ApiOperation,
  ApiQuery,
  ApiResponse,
  ApiTags,
} from '@nestjs/swagger';
import { DeleteUserDto } from './dto/delete-user.dto';
import { AddPostUserDto } from './dto/addPost-user.dto';
import { SetUserNameDto } from './dto/setName-user.dto';
import { BadRequest } from '../entity/badrequest.entity';
import { AuthGuard } from '../auth/auth.guard';
import { Session } from '../auth/session.decorator';
import { SessionContainer } from 'supertokens-node/lib/build/recipe/session/faunadb';

function checkUserDtoEmail(userDtoEmail) {
  if (userDtoEmail === undefined) {
    throw new BadRequestException({
      status: HttpStatus.BAD_REQUEST,
      error: 'You must have an email',
    });
  } else if (typeof userDtoEmail !== 'string') {
    throw new BadRequestException({
      status: HttpStatus.BAD_REQUEST,
      error: 'Email must be a string',
    });
  } else if (userDtoEmail.length == 0) {
    throw new BadRequestException({
      status: HttpStatus.BAD_REQUEST,
      error: "Email can't be Empty",
    });
  }
}

@ApiTags('users')
@Controller('users')
export class UsersController {
  constructor(private usersService: UsersService) {}

  @Post()
  @ApiOperation({ summary: 'Create user' })
  @ApiBody({ type: CreateUserDto })
  @ApiResponse({
    status: 201,
    description: 'Created user',
    type: User,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async create(@Body() createUserDto: CreateUserDto) {
    checkUserDtoEmail(createUserDto.email);
    if (
      createUserDto.name !== undefined &&
      typeof createUserDto.name !== 'string'
    ) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'If you have a name it must be a string',
      });
    } else if (
      createUserDto.name !== undefined &&
      createUserDto.name.length == 0
    ) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "If you have a name it can't be Empty",
      });
    }
    return await this.usersService.create(createUserDto);
  }

  @Delete()
  @ApiOperation({ summary: 'Delete user' })
  @ApiBody({ type: DeleteUserDto })
  @ApiResponse({
    status: 200,
    description: 'Deleted user',
    type: User,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async delete(@Body() deleteUserDto: DeleteUserDto) {
    checkUserDtoEmail(deleteUserDto.email);
    return await this.usersService.delete(deleteUserDto);
  }

  @Get()
  @ApiCookieAuth('sAccessToken')
  @UseGuards(AuthGuard)
  @ApiOperation({ summary: 'Get all users' })
  @ApiQuery({ description: 'Page number', name: 'page', required: false })
  @ApiResponse({
    status: 200,
    description: 'All Users',
    type: [User],
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async findAll(
    @Session() session: SessionContainer,
    @Query('page') page: number,
  ) {
    if (page < 1) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "Page can't be less than 1",
      });
    }
    return await this.usersService.findAll(page);
  }

  @Put()
  @ApiOperation({ summary: 'Set user name' })
  @ApiBody({ type: SetUserNameDto })
  @ApiResponse({
    status: 200,
    description: 'Updated User',
    type: User,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async setUserName(@Body() setUserNameDto: SetUserNameDto) {
    checkUserDtoEmail(setUserNameDto.email);
    if (setUserNameDto.name === undefined) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'You must have a name',
      });
    } else if (typeof setUserNameDto.name !== 'string') {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'Name must be a string',
      });
    } else if (setUserNameDto.name.length == 0) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "Name can't be Empty",
      });
    }
    return await this.usersService.setUserName(setUserNameDto);
  }

  @Put('postId')
  @ApiOperation({ summary: 'Add post for user' })
  @ApiBody({ type: AddPostUserDto })
  @ApiResponse({
    status: 200,
    description: 'Updated User',
    type: User,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async addPostForUser(@Body() addPostUserDto: AddPostUserDto) {
    checkUserDtoEmail(addPostUserDto.email);
    if (addPostUserDto.postId === undefined) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'You must have a postId',
      });
    } else if (typeof addPostUserDto.postId !== 'number') {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'PostId must be a number',
      });
    } else if (addPostUserDto.postId < 0) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "PostId can't be less than 0",
      });
    }
    return await this.usersService.addPostForUser(addPostUserDto);
  }
}
