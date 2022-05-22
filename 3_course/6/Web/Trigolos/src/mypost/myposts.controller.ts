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
} from '@nestjs/common';
import { MyPostsService } from './myposts.service';
import { CreateMyPostDto } from './dto/create-mypost.dto';
import { MyPost } from './entity/mypost.entity';
import {
  ApiBody,
  ApiOperation,
  ApiQuery,
  ApiResponse,
  ApiTags,
} from '@nestjs/swagger';
import { DeleteMyPostDto } from './dto/delete-mypost.dto';
import { PublishMyPostDto } from './dto/publish-mypost.dto';
import { NewContentMyPostDto } from './dto/newContent-mypost.dto';
import { BadRequest } from '../entity/badrequest.entity';

function checkMyPostDtoId(myPostDtoId) {
  if (myPostDtoId === undefined) {
    throw new BadRequestException({
      status: HttpStatus.BAD_REQUEST,
      error: 'You must have an id',
    });
  } else if (typeof myPostDtoId !== 'number') {
    throw new BadRequestException({
      status: HttpStatus.BAD_REQUEST,
      error: 'PostId must be a number',
    });
  } else if (myPostDtoId < 0) {
    throw new BadRequestException({
      status: HttpStatus.BAD_REQUEST,
      error: "PostId can't be less than 0",
    });
  }
}

@ApiTags('mypost')
@Controller('mypost')
export class MyPostsController {
  constructor(private myPostsService: MyPostsService) {}

  @Post()
  @ApiBody({ type: CreateMyPostDto })
  @ApiOperation({ summary: 'Create post' })
  @ApiResponse({
    status: 201,
    description: 'Created post',
    type: MyPost,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async create(@Body() createMyPostDto: CreateMyPostDto) {
    if (createMyPostDto.title === undefined) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'You must have a title',
      });
    } else if (typeof createMyPostDto.title !== 'string') {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'Title must be a string',
      });
    } else if (createMyPostDto.title.length == 0) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "Title can't be Empty",
      });
    } else if (
      createMyPostDto.content !== undefined &&
      typeof createMyPostDto.content !== 'string'
    ) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'If you have a content it must be a string',
      });
    } else if (
      createMyPostDto.content !== undefined &&
      createMyPostDto.content.length == 0
    ) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "If you have a content it can't be Empty",
      });
    } else if (
      createMyPostDto.authorId !== undefined &&
      typeof createMyPostDto.authorId !== 'number'
    ) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'If you have an authorId it must be a number',
      });
    } else if (
      createMyPostDto.authorId !== undefined &&
      createMyPostDto.authorId < 0
    ) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "If you have an authorId it can't be less than 0",
      });
    }
    return await this.myPostsService.create(createMyPostDto);
  }

  @Delete()
  @ApiOperation({ summary: 'Delete post' })
  @ApiBody({ type: DeleteMyPostDto })
  @ApiResponse({
    status: 200,
    description: 'Deleted user',
    type: MyPost,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async delete(@Body() deleteMyPostDto: DeleteMyPostDto) {
    checkMyPostDtoId(deleteMyPostDto.id);
    return await this.myPostsService.delete(deleteMyPostDto);
  }

  @Get()
  @ApiOperation({ summary: 'Get all posts' })
  @ApiQuery({ description: 'Page number', name: 'page', required: false })
  @ApiResponse({
    status: 200,
    description: 'All Posts',
    type: [MyPost],
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async findAll(@Query('page') page: number) {
    if (page < 1) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "Page can't be less than 1",
      });
    }
    return await this.myPostsService.findAll(page);
  }

  @Put()
  @ApiOperation({ summary: 'Publish post' })
  @ApiBody({ type: PublishMyPostDto })
  @ApiResponse({
    status: 200,
    description: 'Publish MyPost',
    type: MyPost,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async publishMyPost(@Body() publishMyPostDto: PublishMyPostDto) {
    checkMyPostDtoId(publishMyPostDto.id);
    return await this.myPostsService.publishMyPost(publishMyPostDto);
  }

  @Put('content')
  @ApiOperation({ summary: 'New post content' })
  @ApiBody({ type: NewContentMyPostDto })
  @ApiResponse({
    status: 200,
    description: 'New content MyPost',
    type: MyPost,
  })
  @ApiResponse({
    status: 400,
    description: 'Error: Bad Request',
    type: BadRequest,
  })
  async newContentMyPost(@Body() newContentMyPostDto: NewContentMyPostDto) {
    checkMyPostDtoId(newContentMyPostDto.id);
    if (newContentMyPostDto.content === undefined) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'You must have a content',
      });
    } else if (typeof newContentMyPostDto.content !== 'string') {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: 'Content must be a string',
      });
    } else if (newContentMyPostDto.content.length == 0) {
      throw new BadRequestException({
        status: HttpStatus.BAD_REQUEST,
        error: "Content can't be Empty",
      });
    }
    return await this.myPostsService.newContentMyPost(newContentMyPostDto);
  }
}
